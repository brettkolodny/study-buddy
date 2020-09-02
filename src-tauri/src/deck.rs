use serde::{Serialize, Deserialize};
use std::fs;

#[derive(Serialize, Deserialize)]
pub struct Deck {
    pub name: String,
    pub cards: Vec<Card>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Card {
    front: String,
    back: String,
    priority: u32,
}

impl Deck {
    pub fn from(deck_string: String) -> Self {

        let deck: Deck = serde_json::from_str(&deck_string).unwrap();

        deck
    }

    pub fn file_is_deck(deck_path: &str) -> bool {
        let deck_string: String = {
            let tmp = fs::read_to_string(deck_path);

            if let Ok(s) = tmp {
                s
            } else {
                return false;
            }
        };

        let deck: Result<Deck, serde_json::Error> = serde_json::from_str(&deck_string);

        if let Ok(_) = deck {
            true
        } else {
            false
        }
    }
}
