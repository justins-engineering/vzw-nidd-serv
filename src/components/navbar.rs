use crate::components::Logo;
use crate::Route;
use dioxus::prelude::*;
use dioxus_free_icons::icons::ld_icons::LdMenu;
use dioxus_free_icons::Icon;

#[component]
pub fn Navbar() -> Element {
  rsx! {
    header { class: "bg-base-100 lg:bg-base-100/90 border-base-300 sticky top-0 z-10 border-b data-[at-top=true]:border-transparent lg:backdrop-blur-sm",
      nav { class: "flex items-center justify-around py-2",
        div { class: "flex items-center gap-2",
          label {
            class: "px-2 swap swap-rotate",
            r#for: "menu-drawer",
            id: "menu-drawer-trigger",
            aria_label: "open sidebar",
            class: "btn btn-square btn-ghost btn-sm",
            Icon { icon: LdMenu }
          }
          Link { to: Route::Index {}, aria_label: "Home", Logo {} }
        }
        div { class: "max-lg:hidden",
          ul { class: "menu menu-horizontal gap-2 px-1 text-base" }
        }
        div { class: "space-x-2",
          Link { class: "btn btn-ghost btn-sm", to: "", "Register" }
          Link { class: "btn btn-primary btn-sm", to: "", "Login" }
        }
      }
      div { class: "drawer",
        input {
          id: "menu-drawer",
          r#type: "checkbox",
          class: "drawer-toggle",
        }
        div { class: "drawer-side",
          label {
            r#for: "menu-drawer",
            aria_label: "close sidebar",
            class: "drawer-overlay",
          }
          div { class: "bg-base-100 min-h-full w-60 p-5",
            Link { to: Route::Index {}, aria_label: "Home", Logo {} }
            ul { class: "menu w-full gap-2 p-0 pt-4" }
          }
        }
      }
    }
  }
}
