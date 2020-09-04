#![cfg_attr(
  all(not(debug_assertions), target_os = "windows"),
  windows_subsystem = "windows"
)]

mod cmd;
mod deck;

use std::fs;
use std::path::PathBuf;
use home;

use serde::Serialize;
use crate::deck::Deck;

#[derive(Serialize)]
struct Reply {
  data: String,
}

fn main() {
  tauri::AppBuilder::new()
    .setup(|webview, _source| {
      let mut webview = webview.as_mut();
      tauri::event::listen(String::from("test"), move |msg| {
        println!("got js-event with message '{:?}'", msg);
        let _reply = Reply {
          data: "test test".to_string(),
        };

        tauri::event::emit(&mut webview, String::from("test-event"), Some("from rust"))
          .expect("failed to emit");
      });
    })
    .invoke_handler(|_webview, arg| {
      use cmd::Cmd::*;
      match serde_json::from_str(arg) {
        Err(e) => {
          Err(e.to_string())
        }
        Ok(command) => {
          match command {
            CreateDeck { deck_name, deck } => {
              let mut buddy_dir = get_buddy_dir().unwrap();

              buddy_dir.push(PathBuf::from(format!("{}.json", deck_name)));
              fs::write(buddy_dir.as_path(), deck.as_bytes()).unwrap();
            },

            ImportDeck { path } => {
              let is_file = Deck::file_is_deck(&path);
              
              if is_file {
                let deck = {
                  let path_split: Vec<&str> = path.split("/").collect();

                  path_split[path_split.len() - 1]
                };

                let mut buddy_dir = get_buddy_dir().unwrap();
                buddy_dir.push(PathBuf::from(deck));
                
                fs::copy(&path, &buddy_dir.as_path());

                let mut webview = _webview.as_mut();
                tauri::event::emit(&mut webview, String::from("update-deck-list"), Some(""))
                  .expect("failed to emit");
              } else {
                dbg!{"is not deck"};
              }
            },

            GetDecks { callback, error }=> {
              #[derive(Serialize)]
              #[serde(rename_all = "camelCase")]
              struct DeckInfo {
                deck_name: String,
                due_cards: String,
                new_cards: String,
              }

              let buddy_dir = get_buddy_dir().unwrap();
              let deck_paths = fs::read_dir(buddy_dir).unwrap();

              let mut decks: Vec<DeckInfo> = Vec::new();

              for deck in deck_paths {
                let deck_name = {
                  let deck_path = deck.unwrap().path();
                  let path_string = deck_path.to_str().unwrap();
                  let path_split: Vec<&str> = path_string.split("/").collect();
                  let deck_file_name = path_split[path_split.len() - 1];

                  let deck_name_split: Vec<&str> = deck_file_name.split(".").collect();

                  deck_name_split[deck_name_split.len() - 2].to_string()
                };

                decks.push(DeckInfo { 
                  deck_name, due_cards: "-1".to_string(), new_cards: "-1".to_string()
                });
              }

              tauri::execute_promise(
                _webview,
                move || Ok(decks),
                callback,
                error,
              )
            }
          }
          Ok(())
        }
      }
    })
    .build()
    .run();
}

fn get_buddy_dir() -> Result<PathBuf, String> {
  if let Some(mut home) = home::home_dir() {
    let buddy_path = PathBuf::from(".studdy_buddy/decks");
    home.push(buddy_path);
    
    if !home.as_path().exists() {
      fs::create_dir_all(home.as_path());
    }

    Ok(home)
  } else {
    Err("Could not locate home directory".to_string())
  }
}