#[macro_use]
extern crate rocket;
use rocket::fs::{FileServer, relative};
// mod vzw {
//   mod credentials;
// }

#[cfg(debug_assertions)]
// If we wanted or needed to serve files manually, we'd use `NamedFile`. Always
// prefer to use `FileServer`!
mod manual {
  use rocket::fs::NamedFile;
  use std::path::{Path, PathBuf};

  #[rocket::get("/second/<path..>")]
  pub async fn second(path: PathBuf) -> Option<NamedFile> {
    let mut path = Path::new(super::relative!("modules/vzw-nidd-front-end/build")).join(path);
    if path.is_dir() {
      path.push("index.html");
    }

    NamedFile::open(path).await.ok()
  }
}

#[get("/hello/<name>")]
fn hello(name: &str) -> String {
  format!("Hello, {name}!")
}

#[get("/vzw/nidd")]
fn vzw_send_nidd() {}

#[get("/vzw/registered_callback_listeners")]
fn vzw_registered_callback_listeners() {}

#[get("/firmware")]
fn firmware_request_handler() {}

#[cfg(debug_assertions)]
#[launch]
fn rocket() -> _ {
  rocket::build()
    .mount("/", rocket::routes![manual::second])
    .mount(
      "/",
      FileServer::from(relative!("modules/vzw-nidd-front-end/build")),
    )
    .mount("/", routes![hello])
}

#[cfg(not(debug_assertions))]
#[launch]
fn rocket() -> _ {
  rocket::build()
    .mount("/", FileServer::from("/srv"))
    .mount("/", routes![hello])
}
