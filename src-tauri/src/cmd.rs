use serde::Deserialize;

#[derive(Deserialize)]
#[serde(tag = "cmd", rename_all = "camelCase")]
pub enum Cmd {
  #[serde(rename_all = "camelCase")]
  CreateDeck { deck_name: String, deck: String },
  ImportDeck { path: String },
  GetDecks { callback: String, error: String },
}
