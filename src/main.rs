#![forbid(unsafe_code)]

use dioxus::logger::tracing::{debug, error};
use dioxus::prelude::*;

// use views::{
//   Index, PageNotFound, ServerError, VerificationFlow,
//   Verify, Wrapper,
// };
use views::{Index, PageNotFound, Wrapper};

#[cfg(feature = "server")]
use ory_kratos_client_wasm::apis::configuration::Configuration;

#[cfg(feature = "server")]
use ory_kratos_client_wasm::apis::metadata_api::{is_alive, is_ready};

mod components;
mod views;

const KRATOS_BROWSER_URL: &str = "http://127.0.0.1:4433";

#[cfg(feature = "server")]
trait Create {
  fn create() -> Configuration;
}

#[cfg(feature = "server")]
impl Create for Configuration {
  fn create() -> Configuration {
    let mut headers = reqwest::header::HeaderMap::with_capacity(1);

    headers.insert(
      reqwest::header::ACCEPT,
      reqwest::header::HeaderValue::from_static("application/json"),
    );

    headers.insert(
      reqwest::header::CONTENT_TYPE,
      reqwest::header::HeaderValue::from_static("application/json"),
    );
    Configuration {
      base_path: KRATOS_BROWSER_URL.to_owned(),
      client: reqwest::ClientBuilder::new()
        .default_headers(headers)
        .build()
        .expect("Failed to build reqwest client"),
      user_agent: None,
      basic_auth: None,
      oauth_access_token: None,
      bearer_access_token: None,
      api_key: None,
    }
  }
}

#[server]
async fn get_server_data() -> Result<String, ServerFnError> {
  return match is_ready(&Configuration::create()).await {
    Ok(r) => {
      debug!("Kratos readiness check: {}", r.status.clone());
      Ok(format!("Kratos readiness check: {}", r.status.to_owned()))
    }
    Err(e) => {
      error!("Kratos readiness check failed! Error: {:?}", e.to_string());
      Ok(format!(
        "Kratos readiness check failed! Error: {:?}",
        e.to_string()
      ))
    }
  };
}

#[derive(Debug, Clone, Routable, PartialEq)]
#[rustfmt::skip]
enum Route {
  #[layout(Wrapper)]
    #[route("/")]
    Index {},
    // #[route("/verify")]
    // Verify {},
    // #[route("/verification?:flow")]
    // VerificationFlow { flow: String },
    #[end_layout]
  #[route("/:..route")]
  PageNotFound { route: Vec<String> },
}

const TAILWIND_CSS: Asset = asset!("/assets/styling/main.css");

fn main() {
  dioxus::launch(App);
}

#[component]
fn App() -> Element {
  rsx! {
    document::Link { rel: "stylesheet", href: TAILWIND_CSS }
    document::Link {
      rel: "icon",
      href: asset!("/assets/images/icon-light.ico"),
      sizes: "32x32",
    }
    document::Link {
      rel: "icon",
      href: asset!("/assets/images/icon-light.ico"),
      sizes: "32x32",
      media: "prefers-color-scheme: light",
    }
    document::Link {
      rel: "icon",
      href: asset!("/assets/images/icon-dark.ico"),
      sizes: "32x32",
      media: "prefers-color-scheme: dark",
    }
    document::Link {
      rel: "icon",
      r#type: "image/svg+xml",
      href: asset!("/assets/images/icon-light.svg"),
    }
    document::Link {
      rel: "icon",
      r#type: "image/svg+xml",
      href: asset!("/assets/images/icon-light.svg"),
      media: "prefers-color-scheme: light",
    }
    document::Link {
      rel: "icon",
      r#type: "image/svg+xml",
      href: asset!("/assets/images/icon-dark.svg"),
      media: "prefers-color-scheme: dark",
    }

    Router::<Route> {}
  }
}
