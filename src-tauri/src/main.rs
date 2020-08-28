#![cfg_attr(
  all(not(debug_assertions), target_os = "windows"),
  windows_subsystem = "windows"
)]

mod cmd;
mod deck;

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
      tauri::event::listen(String::from("js-event"), move |msg| {
        println!("got js-event with message '{:?}'", msg);
        let deck = Deck::test();
        let _reply = Reply {
          data: "test test".to_string(),
        };

        tauri::event::emit(&mut webview, String::from("rust-event"), Some(deck))
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
            // definitions for your custom commands from Cmd here
            MyCustomCommand { argument } => {
              //  your command code
              println!("{}", argument);
            },
            CreateDeck { argument } => {
              let deck = Deck::from(argument);
              println!("{:?}", deck.cards);
            }
          }
          Ok(())
        }
      }
    })
    .build()
    .run();
}
