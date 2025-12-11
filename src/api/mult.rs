// https://github.com/jongiddy/cf-dioxus

#[derive(serde::Deserialize, serde::Serialize)]
pub struct MultiplyRequest {
  pub factor1: i32,
  pub factor2: i32,
}

#[derive(serde::Deserialize, serde::Serialize)]
pub struct MultiplyResponse {
  pub product: i32,
}
