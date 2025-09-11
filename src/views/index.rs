use crate::get_server_data;
use dioxus::prelude::*;

#[component]
pub fn Index() -> Element {
  let count = use_server_future(|| async move { get_server_data().await })?;

  return match &*count.read() {
    Some(result) => match result {
      Ok(status) => {
        rsx! {
          p { {status.to_owned()} }
        }
      }
      Err(err) => {
        rsx! {
          p { {format!("{err:?}")} }
        }
      }
    },
    None => rsx! {
      p { "Waiting..." }
    },
  };
}
