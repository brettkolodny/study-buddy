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
              #[serde(tag = "cmd", rename_all = "camelCase")]
              struct DeckInfo {
                deck_name: String,
                due_cards: String,
                new_cards: String,
              }

              let test = DeckInfo { 
                deck_name: "Bio".to_string(),
                due_cards: "10".to_string(),
                new_cards: "10".to_string(),
              };

              tauri::execute_promise(
                _webview,
                move || Ok(test),
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