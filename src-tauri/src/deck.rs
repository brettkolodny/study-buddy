use serde::{Serialize, Deserialize};

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

    pub fn test() -> Self {
        let card1 = Card { 
            front: String::from("side1"), 
            back: String::from("side2"),
            priority: 0
        };

        let card2 = Card { 
            front: String::from("side1"), 
            back: String::from("side2"),
            priority: 0
        };

        let cards = vec![card1, card2];

        Deck { name: "test".to_string(), cards }
    }
}
