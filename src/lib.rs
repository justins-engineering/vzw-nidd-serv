// https://github.com/jongiddy/cf-dioxus

#![allow(non_snake_case)]

use dioxus::prelude::*;

#[cfg(feature = "api")]
mod api;

#[derive(Debug, Clone, Routable, PartialEq)]
#[rustfmt::skip]
enum Route {
    #[route("/")]
    Home {},
}

const FAVICON: Asset = asset!("assets/images/icon-dark.ico");
const MAIN_CSS: Asset = asset!("/assets/styling/main.css");

#[component]
pub fn App() -> Element {
  rsx! {
    document::Link { rel: "icon", href: FAVICON }
    document::Link { rel: "stylesheet", href: MAIN_CSS }
    Router::<Route> {}
  }
}

/// Home page
#[component]
fn Home() -> Element {
  let mut factor1 = use_signal(|| 1i32);
  let mut factor2 = use_signal(|| 1i32);
  #[allow(unused_mut)]
  let mut opacity = use_signal(|| 1.0);

  #[cfg(feature = "api")]
  let answer = {
    // In Dioxus 0.6 the resource state does not change after the first call.
    // To change state *during* a call, add it to the async call (as for
    // `opacity` here). In Dioxus 0.7 the resource state changes during each call:
    // https://github.com/jongiddy/cf-dioxus/blob/d1b8f6d/cf-dioxus/src/lib.rs#L46-L51
    let multiplication = use_resource(move || async move {
      opacity.set(0.5);
      let multiplication = api::multiply(factor1(), factor2()).await;
      opacity.set(1.0);
      multiplication
    });
    let mut answer = use_signal(|| "= ?".to_string());
    use_effect(move || {
      answer.set(match &*multiplication.read() {
        Some(Ok(product)) => format!("= {product}"),
        Some(Err(err)) => err.to_string(),
        None => "= ?".to_string(),
      });
    });
    answer
  };

  #[cfg(feature = "server-fn")]
  let answer = {
    let multiplication = use_resource(move || async move {
      opacity.set(0.5);
      let multiplication = server_function::multiply(factor1(), factor2()).await;
      opacity.set(1.0);
      multiplication
    });
    let mut answer = use_signal(|| "= ?".to_string());
    use_effect(move || {
      answer.set(match &*multiplication.read() {
        Some(Ok(product)) => format!("= {product}"),
        Some(Err(err)) => err.to_string(),
        None => "= ?".to_string(),
      });
    });
    answer
  };

  rsx! {
    div { display: "flex", flex: "1 1 auto", justify_content: "center",
      div {
        display: "grid",
        grid_template_columns: "2cm 50px 2cm 4cm",

        align_items: "center",
        justify_items: "center",

        // Top row
        div {
          button {
            onclick: move |_| {
                factor1 += 1;
            },
            "+"
          }
        }
        div {}
        div {
          button {
            onclick: move |_| {
                factor2 += 1;
            },
            "+"
          }
        }
        div {}

        // Middle row
        div { "{factor1}" }
        div { dangerous_inner_html: "&times;" }
        div { "{factor2}" }
        div { opacity: "{opacity}", "{answer}" }

        // Bottom row
        div {
          button {
            onclick: move |_| {
                factor1 -= 1;
            },
            "-"
          }
        }
        div {}
        div {
          button {
            onclick: move |_| {
                factor2 -= 1;
            },
            "-"
          }
        }
        div {}
      }

    }
  }
}
