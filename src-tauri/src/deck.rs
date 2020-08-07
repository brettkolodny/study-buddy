use serde::Serialize;

#[derive(Serialize)]
pub struct Deck {
    cards: Vec<Card>
}

#[derive(Serialize)]
struct Card {
    front: String,
    back: String,
    priority: u32,
}

impl Deck {
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

        Deck { cards }
    }
}
