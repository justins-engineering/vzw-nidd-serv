var __defProp = Object.defineProperty;
var __name = (target, value) => __defProp(target, "name", { value, configurable: true });

// build/worker/shim.mjs
import Jt from "./c735b24312b46aa068836a1f178c8ff1a23675c2-index.wasm";
import { WorkerEntrypoint as Yt } from "cloudflare:workers";
var W = Object.defineProperty;
var B = /* @__PURE__ */ __name((e3, t) => {
  for (var n in t) W(e3, n, { get: t[n], enumerable: true });
}, "B");
var w = {};
B(w, { IntoUnderlyingByteSource: /* @__PURE__ */ __name(() => k, "IntoUnderlyingByteSource"), IntoUnderlyingSink: /* @__PURE__ */ __name(() => T, "IntoUnderlyingSink"), IntoUnderlyingSource: /* @__PURE__ */ __name(() => F, "IntoUnderlyingSource"), MinifyConfig: /* @__PURE__ */ __name(() => S, "MinifyConfig"), PolishConfig: /* @__PURE__ */ __name(() => Y, "PolishConfig"), R2Range: /* @__PURE__ */ __name(() => z, "R2Range"), RequestRedirect: /* @__PURE__ */ __name(() => v, "RequestRedirect"), __wbg_Error_0497d5bdba9362e5: /* @__PURE__ */ __name(() => te, "__wbg_Error_0497d5bdba9362e5"), __wbg_String_8f0eb39a4a4c2f66: /* @__PURE__ */ __name(() => ne, "__wbg_String_8f0eb39a4a4c2f66"), __wbg_append_0342728346e47425: /* @__PURE__ */ __name(() => re, "__wbg_append_0342728346e47425"), __wbg_body_3ee5f3b57855c324: /* @__PURE__ */ __name(() => _e, "__wbg_body_3ee5f3b57855c324"), __wbg_body_e1e045c770257634: /* @__PURE__ */ __name(() => oe, "__wbg_body_e1e045c770257634"), __wbg_buffer_a1a27a0dfa70165d: /* @__PURE__ */ __name(() => ce, "__wbg_buffer_a1a27a0dfa70165d"), __wbg_buffer_e495ba54cee589cc: /* @__PURE__ */ __name(() => ie, "__wbg_buffer_e495ba54cee589cc"), __wbg_byobRequest_56aa768ee4dfed17: /* @__PURE__ */ __name(() => se, "__wbg_byobRequest_56aa768ee4dfed17"), __wbg_byteLength_937f8a52f9697148: /* @__PURE__ */ __name(() => ue, "__wbg_byteLength_937f8a52f9697148"), __wbg_byteOffset_4d94b7170e641898: /* @__PURE__ */ __name(() => fe, "__wbg_byteOffset_4d94b7170e641898"), __wbg_call_f2db6205e5c51dc8: /* @__PURE__ */ __name(() => ae, "__wbg_call_f2db6205e5c51dc8"), __wbg_call_fbe8be8bf6436ce5: /* @__PURE__ */ __name(() => be, "__wbg_call_fbe8be8bf6436ce5"), __wbg_cancel_4d78160f447bbbeb: /* @__PURE__ */ __name(() => ge, "__wbg_cancel_4d78160f447bbbeb"), __wbg_catch_b51fce253ee18ec3: /* @__PURE__ */ __name(() => de, "__wbg_catch_b51fce253ee18ec3"), __wbg_cause_af6ef82a8abe435b: /* @__PURE__ */ __name(() => we, "__wbg_cause_af6ef82a8abe435b"), __wbg_cf_475e858e5c5db972: /* @__PURE__ */ __name(() => le, "__wbg_cf_475e858e5c5db972"), __wbg_cf_60aafe7bb03e919a: /* @__PURE__ */ __name(() => pe, "__wbg_cf_60aafe7bb03e919a"), __wbg_close_290fb040af98d3ac: /* @__PURE__ */ __name(() => xe, "__wbg_close_290fb040af98d3ac"), __wbg_close_b2641ef0870e518c: /* @__PURE__ */ __name(() => ye, "__wbg_close_b2641ef0870e518c"), __wbg_constructor_1a4f07ad72d5cac3: /* @__PURE__ */ __name(() => he, "__wbg_constructor_1a4f07ad72d5cac3"), __wbg_done_4d01f352bade43b7: /* @__PURE__ */ __name(() => me, "__wbg_done_4d01f352bade43b7"), __wbg_enqueue_a62faa171c4fd287: /* @__PURE__ */ __name(() => Re, "__wbg_enqueue_a62faa171c4fd287"), __wbg_entries_1532c722e9a3517c: /* @__PURE__ */ __name(() => Fe, "__wbg_entries_1532c722e9a3517c"), __wbg_error_51ecdd39ec054205: /* @__PURE__ */ __name(() => Se, "__wbg_error_51ecdd39ec054205"), __wbg_error_7534b8e9a36f1ab4: /* @__PURE__ */ __name(() => Ee, "__wbg_error_7534b8e9a36f1ab4"), __wbg_fetch_cd6e56bd3dd22dd0: /* @__PURE__ */ __name(() => Oe, "__wbg_fetch_cd6e56bd3dd22dd0"), __wbg_fetch_ed0fd2c8ad4bc3a3: /* @__PURE__ */ __name(() => Ie, "__wbg_fetch_ed0fd2c8ad4bc3a3"), __wbg_getReader_48e00749fe3f6089: /* @__PURE__ */ __name(() => ke, "__wbg_getReader_48e00749fe3f6089"), __wbg_get_92470be87867c2e5: /* @__PURE__ */ __name(() => Te, "__wbg_get_92470be87867c2e5"), __wbg_get_a131a44bd1eb6979: /* @__PURE__ */ __name(() => ze, "__wbg_get_a131a44bd1eb6979"), __wbg_getdone_8355ddb2bc75c731: /* @__PURE__ */ __name(() => Me, "__wbg_getdone_8355ddb2bc75c731"), __wbg_getvalue_c1890a401d13f00b: /* @__PURE__ */ __name(() => je, "__wbg_getvalue_c1890a401d13f00b"), __wbg_headers_0f0cbdc6290b6780: /* @__PURE__ */ __name(() => Ae, "__wbg_headers_0f0cbdc6290b6780"), __wbg_headers_67fbc7839fe933b3: /* @__PURE__ */ __name(() => Le, "__wbg_headers_67fbc7839fe933b3"), __wbg_httpProtocol_a32dd935f614e790: /* @__PURE__ */ __name(() => qe, "__wbg_httpProtocol_a32dd935f614e790"), __wbg_instanceof_Error_58a92d81483a4b16: /* @__PURE__ */ __name(() => De, "__wbg_instanceof_Error_58a92d81483a4b16"), __wbg_instanceof_Response_e80ce8b7a2b968d2: /* @__PURE__ */ __name(() => Ce, "__wbg_instanceof_Response_e80ce8b7a2b968d2"), __wbg_length_ab6d22b5ead75c72: /* @__PURE__ */ __name(() => Ue, "__wbg_length_ab6d22b5ead75c72"), __wbg_log_ea240990d83e374e: /* @__PURE__ */ __name(() => We, "__wbg_log_ea240990d83e374e"), __wbg_method_a3a2d7fac54c95f8: /* @__PURE__ */ __name(() => Be, "__wbg_method_a3a2d7fac54c95f8"), __wbg_minifyconfig_new: /* @__PURE__ */ __name(() => Pe, "__wbg_minifyconfig_new"), __wbg_name_5503b7b8010787c5: /* @__PURE__ */ __name(() => $e, "__wbg_name_5503b7b8010787c5"), __wbg_new_07b483f72211fd66: /* @__PURE__ */ __name(() => Ne, "__wbg_new_07b483f72211fd66"), __wbg_new_476169e6d59f23ae: /* @__PURE__ */ __name(() => Ve, "__wbg_new_476169e6d59f23ae"), __wbg_new_4796e1cd2eb9ea6d: /* @__PURE__ */ __name(() => Xe, "__wbg_new_4796e1cd2eb9ea6d"), __wbg_new_8a6f238a6ece86ea: /* @__PURE__ */ __name(() => Ge, "__wbg_new_8a6f238a6ece86ea"), __wbg_new_a979b4b45bd55c7f: /* @__PURE__ */ __name(() => He, "__wbg_new_a979b4b45bd55c7f"), __wbg_new_e30c39c06edaabf2: /* @__PURE__ */ __name(() => Je, "__wbg_new_e30c39c06edaabf2"), __wbg_new_e52b3efaaa774f96: /* @__PURE__ */ __name(() => Ye, "__wbg_new_e52b3efaaa774f96"), __wbg_newnoargs_ff528e72d35de39a: /* @__PURE__ */ __name(() => ve, "__wbg_newnoargs_ff528e72d35de39a"), __wbg_newwithbyteoffsetandlength_3b01ecda099177e8: /* @__PURE__ */ __name(() => Ke, "__wbg_newwithbyteoffsetandlength_3b01ecda099177e8"), __wbg_newwithintounderlyingsource_b47f6a6a596a7f24: /* @__PURE__ */ __name(() => Qe, "__wbg_newwithintounderlyingsource_b47f6a6a596a7f24"), __wbg_newwithlength_08f872dc1e3ada2e: /* @__PURE__ */ __name(() => Ze, "__wbg_newwithlength_08f872dc1e3ada2e"), __wbg_newwithoptbuffersourceandinit_b77afe7366f846b5: /* @__PURE__ */ __name(() => et, "__wbg_newwithoptbuffersourceandinit_b77afe7366f846b5"), __wbg_newwithoptreadablestreamandinit_ce4ecbe22555867e: /* @__PURE__ */ __name(() => tt, "__wbg_newwithoptreadablestreamandinit_ce4ecbe22555867e"), __wbg_newwithoptstrandinit_8128e018ed06a4f8: /* @__PURE__ */ __name(() => nt, "__wbg_newwithoptstrandinit_8128e018ed06a4f8"), __wbg_next_e2da48d8fff7439a: /* @__PURE__ */ __name(() => rt, "__wbg_next_e2da48d8fff7439a"), __wbg_queueMicrotask_46c1df247678729f: /* @__PURE__ */ __name(() => _t, "__wbg_queueMicrotask_46c1df247678729f"), __wbg_queueMicrotask_8acf3ccb75ed8d11: /* @__PURE__ */ __name(() => ot, "__wbg_queueMicrotask_8acf3ccb75ed8d11"), __wbg_read_f4b89f69cc51efc7: /* @__PURE__ */ __name(() => ct, "__wbg_read_f4b89f69cc51efc7"), __wbg_redirect_103cbb9748d5ac32: /* @__PURE__ */ __name(() => it, "__wbg_redirect_103cbb9748d5ac32"), __wbg_releaseLock_c589dd51c0812aca: /* @__PURE__ */ __name(() => st, "__wbg_releaseLock_c589dd51c0812aca"), __wbg_resolve_0dac8c580ffd4678: /* @__PURE__ */ __name(() => ut, "__wbg_resolve_0dac8c580ffd4678"), __wbg_respond_b227f1c3be2bb879: /* @__PURE__ */ __name(() => ft, "__wbg_respond_b227f1c3be2bb879"), __wbg_set_3f1d0b984ed272ed: /* @__PURE__ */ __name(() => at, "__wbg_set_3f1d0b984ed272ed"), __wbg_set_c43293f93a35998a: /* @__PURE__ */ __name(() => bt, "__wbg_set_c43293f93a35998a"), __wbg_set_d6bdfd275fb8a4ce: /* @__PURE__ */ __name(() => gt, "__wbg_set_d6bdfd275fb8a4ce"), __wbg_set_fe4e79d1ed3b0e9b: /* @__PURE__ */ __name(() => dt, "__wbg_set_fe4e79d1ed3b0e9b"), __wbg_set_wasm: /* @__PURE__ */ __name(() => M, "__wbg_set_wasm"), __wbg_setbody_971ec015fc13d6b4: /* @__PURE__ */ __name(() => wt, "__wbg_setbody_971ec015fc13d6b4"), __wbg_setheaders_408564032a1382da: /* @__PURE__ */ __name(() => lt, "__wbg_setheaders_408564032a1382da"), __wbg_setheaders_65a4eb4c0443ae61: /* @__PURE__ */ __name(() => pt, "__wbg_setheaders_65a4eb4c0443ae61"), __wbg_sethighwatermark_3017ad772d071dcb: /* @__PURE__ */ __name(() => xt, "__wbg_sethighwatermark_3017ad772d071dcb"), __wbg_setmethod_8ce1be0b4d701b7c: /* @__PURE__ */ __name(() => yt, "__wbg_setmethod_8ce1be0b4d701b7c"), __wbg_setredirect_562df6aa76f9dd5a: /* @__PURE__ */ __name(() => ht, "__wbg_setredirect_562df6aa76f9dd5a"), __wbg_setstatus_bd5b448a903a8658: /* @__PURE__ */ __name(() => mt, "__wbg_setstatus_bd5b448a903a8658"), __wbg_signal_a393dc337ddce436: /* @__PURE__ */ __name(() => Rt, "__wbg_signal_a393dc337ddce436"), __wbg_stack_0ed75d68575b0f3c: /* @__PURE__ */ __name(() => Ft, "__wbg_stack_0ed75d68575b0f3c"), __wbg_static_accessor_GLOBAL_487c52c58d65314d: /* @__PURE__ */ __name(() => St, "__wbg_static_accessor_GLOBAL_487c52c58d65314d"), __wbg_static_accessor_GLOBAL_THIS_ee9704f328b6b291: /* @__PURE__ */ __name(() => Et, "__wbg_static_accessor_GLOBAL_THIS_ee9704f328b6b291"), __wbg_static_accessor_SELF_78c9e3071b912620: /* @__PURE__ */ __name(() => Ot, "__wbg_static_accessor_SELF_78c9e3071b912620"), __wbg_static_accessor_WINDOW_a093d21393777366: /* @__PURE__ */ __name(() => It, "__wbg_static_accessor_WINDOW_a093d21393777366"), __wbg_status_a54682bbe52f9058: /* @__PURE__ */ __name(() => kt, "__wbg_status_a54682bbe52f9058"), __wbg_then_82ab9fb4080f1707: /* @__PURE__ */ __name(() => Tt, "__wbg_then_82ab9fb4080f1707"), __wbg_then_db882932c0c714c6: /* @__PURE__ */ __name(() => zt, "__wbg_then_db882932c0c714c6"), __wbg_toString_21791a66666b3afd: /* @__PURE__ */ __name(() => Mt, "__wbg_toString_21791a66666b3afd"), __wbg_url_f1c3162019331231: /* @__PURE__ */ __name(() => jt, "__wbg_url_f1c3162019331231"), __wbg_value_17b896954e14f896: /* @__PURE__ */ __name(() => At, "__wbg_value_17b896954e14f896"), __wbg_view_a9ad80dcbad7cf1c: /* @__PURE__ */ __name(() => Lt, "__wbg_view_a9ad80dcbad7cf1c"), __wbg_webSocket_38528fcd2e5cba7f: /* @__PURE__ */ __name(() => qt, "__wbg_webSocket_38528fcd2e5cba7f"), __wbindgen_cb_drop: /* @__PURE__ */ __name(() => Dt, "__wbindgen_cb_drop"), __wbindgen_closure_wrapper1590: /* @__PURE__ */ __name(() => Ct, "__wbindgen_closure_wrapper1590"), __wbindgen_debug_string: /* @__PURE__ */ __name(() => Ut, "__wbindgen_debug_string"), __wbindgen_init_externref_table: /* @__PURE__ */ __name(() => Wt, "__wbindgen_init_externref_table"), __wbindgen_is_function: /* @__PURE__ */ __name(() => Bt, "__wbindgen_is_function"), __wbindgen_is_string: /* @__PURE__ */ __name(() => Pt, "__wbindgen_is_string"), __wbindgen_is_undefined: /* @__PURE__ */ __name(() => $t, "__wbindgen_is_undefined"), __wbindgen_memory: /* @__PURE__ */ __name(() => Nt, "__wbindgen_memory"), __wbindgen_number_new: /* @__PURE__ */ __name(() => Vt, "__wbindgen_number_new"), __wbindgen_string_get: /* @__PURE__ */ __name(() => Xt, "__wbindgen_string_get"), __wbindgen_string_new: /* @__PURE__ */ __name(() => Gt, "__wbindgen_string_new"), __wbindgen_throw: /* @__PURE__ */ __name(() => Ht, "__wbindgen_throw"), fetch: /* @__PURE__ */ __name(() => j, "fetch"), start: /* @__PURE__ */ __name(() => G, "start") });
var r;
function M(e3) {
  r = e3;
}
__name(M, "M");
var y = null;
function h() {
  return (y === null || y.byteLength === 0) && (y = new Uint8Array(r.memory.buffer)), y;
}
__name(h, "h");
var D = typeof TextDecoder > "u" ? (0, module.require)("util").TextDecoder : TextDecoder;
var m = new D("utf-8", { ignoreBOM: true, fatal: true });
m.decode();
var P = 2146435072;
var O = 0;
function $(e3, t) {
  return O += t, O >= P && (m = new D("utf-8", { ignoreBOM: true, fatal: true }), m.decode(), O = t), m.decode(h().subarray(e3, e3 + t));
}
__name($, "$");
function b(e3, t) {
  return e3 = e3 >>> 0, $(e3, t);
}
__name(b, "b");
var d = 0;
var N = typeof TextEncoder > "u" ? (0, module.require)("util").TextEncoder : TextEncoder;
var R = new N("utf-8");
var V = typeof R.encodeInto == "function" ? function(e3, t) {
  return R.encodeInto(e3, t);
} : function(e3, t) {
  let n = R.encode(e3);
  return t.set(n), { read: e3.length, written: n.length };
};
function l(e3, t, n) {
  if (n === void 0) {
    let u = R.encode(e3), x = t(u.length, 1) >>> 0;
    return h().subarray(x, x + u.length).set(u), d = u.length, x;
  }
  let _ = e3.length, o = t(_, 1) >>> 0, f = h(), i = 0;
  for (; i < _; i++) {
    let u = e3.charCodeAt(i);
    if (u > 127) break;
    f[o + i] = u;
  }
  if (i !== _) {
    i !== 0 && (e3 = e3.slice(i)), o = n(o, _, _ = i + e3.length * 3, 1) >>> 0;
    let u = h().subarray(o + i, o + _), x = V(e3, u);
    i += x.written, o = n(o, _, i, 1) >>> 0;
  }
  return d = i, o;
}
__name(l, "l");
var p = null;
function a() {
  return (p === null || p.buffer.detached === true || p.buffer.detached === void 0 && p.buffer !== r.memory.buffer) && (p = new DataView(r.memory.buffer)), p;
}
__name(a, "a");
function g(e3) {
  let t = r.__externref_table_alloc();
  return r.__wbindgen_export_4.set(t, e3), t;
}
__name(g, "g");
function c(e3, t) {
  try {
    return e3.apply(this, t);
  } catch (n) {
    let _ = g(n);
    r.__wbindgen_exn_store(_);
  }
}
__name(c, "c");
function s(e3) {
  return e3 == null;
}
__name(s, "s");
var A = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => {
  r.__wbindgen_export_6.get(e3.dtor)(e3.a, e3.b);
});
function X(e3, t, n, _) {
  let o = { a: e3, b: t, cnt: 1, dtor: n }, f = /* @__PURE__ */ __name((...i) => {
    o.cnt++;
    let u = o.a;
    o.a = 0;
    try {
      return _(u, o.b, ...i);
    } finally {
      --o.cnt === 0 ? (r.__wbindgen_export_6.get(o.dtor)(u, o.b), A.unregister(o)) : o.a = u;
    }
  }, "f");
  return f.original = o, A.register(f, o, o), f;
}
__name(X, "X");
function I(e3) {
  let t = typeof e3;
  if (t == "number" || t == "boolean" || e3 == null) return `${e3}`;
  if (t == "string") return `"${e3}"`;
  if (t == "symbol") {
    let o = e3.description;
    return o == null ? "Symbol" : `Symbol(${o})`;
  }
  if (t == "function") {
    let o = e3.name;
    return typeof o == "string" && o.length > 0 ? `Function(${o})` : "Function";
  }
  if (Array.isArray(e3)) {
    let o = e3.length, f = "[";
    o > 0 && (f += I(e3[0]));
    for (let i = 1; i < o; i++) f += ", " + I(e3[i]);
    return f += "]", f;
  }
  let n = /\[object ([^\]]+)\]/.exec(toString.call(e3)), _;
  if (n && n.length > 1) _ = n[1];
  else return toString.call(e3);
  if (_ == "Object") try {
    return "Object(" + JSON.stringify(e3) + ")";
  } catch {
    return "Object";
  }
  return e3 instanceof Error ? `${e3.name}: ${e3.message}
${e3.stack}` : _;
}
__name(I, "I");
function G() {
  r.start();
}
__name(G, "G");
function j(e3, t, n) {
  return r.fetch(e3, t, n);
}
__name(j, "j");
function H(e3, t, n) {
  r.closure325_externref_shim(e3, t, n);
}
__name(H, "H");
function J(e3, t, n, _) {
  r.closure346_externref_shim(e3, t, n, _);
}
__name(J, "J");
var Y = Object.freeze({ Off: 0, 0: "Off", Lossy: 1, 1: "Lossy", Lossless: 2, 2: "Lossless" });
var v = Object.freeze({ Error: 0, 0: "Error", Follow: 1, 1: "Follow", Manual: 2, 2: "Manual" });
var K = ["bytes"];
var C = ["follow", "error", "manual"];
var Q = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => r.__wbg_intounderlyingbytesource_free(e3 >>> 0, 1));
var k = class {
  static {
    __name(this, "k");
  }
  __destroy_into_raw() {
    let t = this.__wbg_ptr;
    return this.__wbg_ptr = 0, Q.unregister(this), t;
  }
  free() {
    let t = this.__destroy_into_raw();
    r.__wbg_intounderlyingbytesource_free(t, 0);
  }
  get type() {
    let t = r.intounderlyingbytesource_type(this.__wbg_ptr);
    return K[t];
  }
  get autoAllocateChunkSize() {
    return r.intounderlyingbytesource_autoAllocateChunkSize(this.__wbg_ptr) >>> 0;
  }
  start(t) {
    r.intounderlyingbytesource_start(this.__wbg_ptr, t);
  }
  pull(t) {
    return r.intounderlyingbytesource_pull(this.__wbg_ptr, t);
  }
  cancel() {
    let t = this.__destroy_into_raw();
    r.intounderlyingbytesource_cancel(t);
  }
};
var Z = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => r.__wbg_intounderlyingsink_free(e3 >>> 0, 1));
var T = class {
  static {
    __name(this, "T");
  }
  __destroy_into_raw() {
    let t = this.__wbg_ptr;
    return this.__wbg_ptr = 0, Z.unregister(this), t;
  }
  free() {
    let t = this.__destroy_into_raw();
    r.__wbg_intounderlyingsink_free(t, 0);
  }
  write(t) {
    return r.intounderlyingsink_write(this.__wbg_ptr, t);
  }
  close() {
    let t = this.__destroy_into_raw();
    return r.intounderlyingsink_close(t);
  }
  abort(t) {
    let n = this.__destroy_into_raw();
    return r.intounderlyingsink_abort(n, t);
  }
};
var L = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => r.__wbg_intounderlyingsource_free(e3 >>> 0, 1));
var F = class e {
  static {
    __name(this, "e");
  }
  static __wrap(t) {
    t = t >>> 0;
    let n = Object.create(e.prototype);
    return n.__wbg_ptr = t, L.register(n, n.__wbg_ptr, n), n;
  }
  __destroy_into_raw() {
    let t = this.__wbg_ptr;
    return this.__wbg_ptr = 0, L.unregister(this), t;
  }
  free() {
    let t = this.__destroy_into_raw();
    r.__wbg_intounderlyingsource_free(t, 0);
  }
  pull(t) {
    return r.intounderlyingsource_pull(this.__wbg_ptr, t);
  }
  cancel() {
    let t = this.__destroy_into_raw();
    r.intounderlyingsource_cancel(t);
  }
};
var q = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => r.__wbg_minifyconfig_free(e3 >>> 0, 1));
var S = class e2 {
  static {
    __name(this, "e");
  }
  static __wrap(t) {
    t = t >>> 0;
    let n = Object.create(e2.prototype);
    return n.__wbg_ptr = t, q.register(n, n.__wbg_ptr, n), n;
  }
  __destroy_into_raw() {
    let t = this.__wbg_ptr;
    return this.__wbg_ptr = 0, q.unregister(this), t;
  }
  free() {
    let t = this.__destroy_into_raw();
    r.__wbg_minifyconfig_free(t, 0);
  }
  get js() {
    return r.__wbg_get_minifyconfig_js(this.__wbg_ptr) !== 0;
  }
  set js(t) {
    r.__wbg_set_minifyconfig_js(this.__wbg_ptr, t);
  }
  get html() {
    return r.__wbg_get_minifyconfig_html(this.__wbg_ptr) !== 0;
  }
  set html(t) {
    r.__wbg_set_minifyconfig_html(this.__wbg_ptr, t);
  }
  get css() {
    return r.__wbg_get_minifyconfig_css(this.__wbg_ptr) !== 0;
  }
  set css(t) {
    r.__wbg_set_minifyconfig_css(this.__wbg_ptr, t);
  }
};
var ee = typeof FinalizationRegistry > "u" ? { register: /* @__PURE__ */ __name(() => {
}, "register"), unregister: /* @__PURE__ */ __name(() => {
}, "unregister") } : new FinalizationRegistry((e3) => r.__wbg_r2range_free(e3 >>> 0, 1));
var z = class {
  static {
    __name(this, "z");
  }
  __destroy_into_raw() {
    let t = this.__wbg_ptr;
    return this.__wbg_ptr = 0, ee.unregister(this), t;
  }
  free() {
    let t = this.__destroy_into_raw();
    r.__wbg_r2range_free(t, 0);
  }
  get offset() {
    let t = r.__wbg_get_r2range_offset(this.__wbg_ptr);
    return t[0] === 0 ? void 0 : t[1];
  }
  set offset(t) {
    r.__wbg_set_r2range_offset(this.__wbg_ptr, !s(t), s(t) ? 0 : t);
  }
  get length() {
    let t = r.__wbg_get_r2range_length(this.__wbg_ptr);
    return t[0] === 0 ? void 0 : t[1];
  }
  set length(t) {
    r.__wbg_set_r2range_length(this.__wbg_ptr, !s(t), s(t) ? 0 : t);
  }
  get suffix() {
    let t = r.__wbg_get_r2range_suffix(this.__wbg_ptr);
    return t[0] === 0 ? void 0 : t[1];
  }
  set suffix(t) {
    r.__wbg_set_r2range_suffix(this.__wbg_ptr, !s(t), s(t) ? 0 : t);
  }
};
function te(e3, t) {
  return Error(b(e3, t));
}
__name(te, "te");
function ne(e3, t) {
  let n = String(t), _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
  a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
}
__name(ne, "ne");
function re() {
  return c(function(e3, t, n, _, o) {
    e3.append(b(t, n), b(_, o));
  }, arguments);
}
__name(re, "re");
function _e(e3) {
  let t = e3.body;
  return s(t) ? 0 : g(t);
}
__name(_e, "_e");
function oe(e3) {
  let t = e3.body;
  return s(t) ? 0 : g(t);
}
__name(oe, "oe");
function ce(e3) {
  return e3.buffer;
}
__name(ce, "ce");
function ie(e3) {
  return e3.buffer;
}
__name(ie, "ie");
function se(e3) {
  let t = e3.byobRequest;
  return s(t) ? 0 : g(t);
}
__name(se, "se");
function ue(e3) {
  return e3.byteLength;
}
__name(ue, "ue");
function fe(e3) {
  return e3.byteOffset;
}
__name(fe, "fe");
function ae() {
  return c(function(e3, t, n) {
    return e3.call(t, n);
  }, arguments);
}
__name(ae, "ae");
function be() {
  return c(function(e3, t) {
    return e3.call(t);
  }, arguments);
}
__name(be, "be");
function ge(e3) {
  return e3.cancel();
}
__name(ge, "ge");
function de(e3, t) {
  return e3.catch(t);
}
__name(de, "de");
function we(e3) {
  return e3.cause;
}
__name(we, "we");
function le() {
  return c(function(e3) {
    let t = e3.cf;
    return s(t) ? 0 : g(t);
  }, arguments);
}
__name(le, "le");
function pe() {
  return c(function(e3) {
    let t = e3.cf;
    return s(t) ? 0 : g(t);
  }, arguments);
}
__name(pe, "pe");
function xe() {
  return c(function(e3) {
    e3.close();
  }, arguments);
}
__name(xe, "xe");
function ye() {
  return c(function(e3) {
    e3.close();
  }, arguments);
}
__name(ye, "ye");
function he(e3) {
  return e3.constructor;
}
__name(he, "he");
function me(e3) {
  return e3.done;
}
__name(me, "me");
function Re() {
  return c(function(e3, t) {
    e3.enqueue(t);
  }, arguments);
}
__name(Re, "Re");
function Fe(e3) {
  return e3.entries();
}
__name(Fe, "Fe");
function Se(e3) {
  console.error(e3);
}
__name(Se, "Se");
function Ee(e3, t) {
  let n, _;
  try {
    n = e3, _ = t, console.error(b(e3, t));
  } finally {
    r.__wbindgen_free(n, _, 1);
  }
}
__name(Ee, "Ee");
function Oe() {
  return c(function(e3, t, n) {
    return e3.fetch(b(t, n));
  }, arguments);
}
__name(Oe, "Oe");
function Ie() {
  return c(function(e3, t, n, _) {
    return e3.fetch(b(t, n), _);
  }, arguments);
}
__name(Ie, "Ie");
function ke() {
  return c(function(e3) {
    return e3.getReader();
  }, arguments);
}
__name(ke, "ke");
function Te() {
  return c(function(e3, t) {
    return Reflect.get(e3, t);
  }, arguments);
}
__name(Te, "Te");
function ze(e3, t) {
  return e3[t >>> 0];
}
__name(ze, "ze");
function Me(e3) {
  let t = e3.done;
  return s(t) ? 16777215 : t ? 1 : 0;
}
__name(Me, "Me");
function je(e3) {
  return e3.value;
}
__name(je, "je");
function Ae(e3) {
  return e3.headers;
}
__name(Ae, "Ae");
function Le(e3) {
  return e3.headers;
}
__name(Le, "Le");
function qe() {
  return c(function(e3, t) {
    let n = t.httpProtocol, _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
    a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
  }, arguments);
}
__name(qe, "qe");
function De(e3) {
  let t;
  try {
    t = e3 instanceof Error;
  } catch {
    t = false;
  }
  return t;
}
__name(De, "De");
function Ce(e3) {
  let t;
  try {
    t = e3 instanceof Response;
  } catch {
    t = false;
  }
  return t;
}
__name(Ce, "Ce");
function Ue(e3) {
  return e3.length;
}
__name(Ue, "Ue");
function We(e3) {
  console.log(e3);
}
__name(We, "We");
function Be(e3, t) {
  let n = t.method, _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
  a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
}
__name(Be, "Be");
function Pe(e3) {
  return S.__wrap(e3);
}
__name(Pe, "Pe");
function $e(e3) {
  return e3.name;
}
__name($e, "$e");
function Ne() {
  return new Object();
}
__name(Ne, "Ne");
function Ve(e3, t) {
  return new Error(b(e3, t));
}
__name(Ve, "Ve");
function Xe() {
  return c(function() {
    return new Headers();
  }, arguments);
}
__name(Xe, "Xe");
function Ge() {
  return new Error();
}
__name(Ge, "Ge");
function He() {
  return /* @__PURE__ */ new Map();
}
__name(He, "He");
function Je(e3, t) {
  try {
    var n = { a: e3, b: t }, _ = /* @__PURE__ */ __name((f, i) => {
      let u = n.a;
      n.a = 0;
      try {
        return J(u, n.b, f, i);
      } finally {
        n.a = u;
      }
    }, "_");
    return new Promise(_);
  } finally {
    n.a = n.b = 0;
  }
}
__name(Je, "Je");
function Ye(e3) {
  return new Uint8Array(e3);
}
__name(Ye, "Ye");
function ve(e3, t) {
  return new Function(b(e3, t));
}
__name(ve, "ve");
function Ke(e3, t, n) {
  return new Uint8Array(e3, t >>> 0, n >>> 0);
}
__name(Ke, "Ke");
function Qe(e3, t) {
  return new ReadableStream(F.__wrap(e3), t);
}
__name(Qe, "Qe");
function Ze(e3) {
  return new Uint8Array(e3 >>> 0);
}
__name(Ze, "Ze");
function et() {
  return c(function(e3, t) {
    return new Response(e3, t);
  }, arguments);
}
__name(et, "et");
function tt() {
  return c(function(e3, t) {
    return new Response(e3, t);
  }, arguments);
}
__name(tt, "tt");
function nt() {
  return c(function(e3, t, n) {
    return new Response(e3 === 0 ? void 0 : b(e3, t), n);
  }, arguments);
}
__name(nt, "nt");
function rt() {
  return c(function(e3) {
    return e3.next();
  }, arguments);
}
__name(rt, "rt");
function _t(e3) {
  queueMicrotask(e3);
}
__name(_t, "_t");
function ot(e3) {
  return e3.queueMicrotask;
}
__name(ot, "ot");
function ct(e3) {
  return e3.read();
}
__name(ct, "ct");
function it(e3) {
  let t = e3.redirect;
  return (C.indexOf(t) + 1 || 4) - 1;
}
__name(it, "it");
function st(e3) {
  e3.releaseLock();
}
__name(st, "st");
function ut(e3) {
  return Promise.resolve(e3);
}
__name(ut, "ut");
function ft() {
  return c(function(e3, t) {
    e3.respond(t >>> 0);
  }, arguments);
}
__name(ft, "ft");
function at(e3, t, n) {
  e3[t] = n;
}
__name(at, "at");
function bt() {
  return c(function(e3, t, n) {
    return Reflect.set(e3, t, n);
  }, arguments);
}
__name(bt, "bt");
function gt(e3, t, n) {
  return e3.set(t, n);
}
__name(gt, "gt");
function dt(e3, t, n) {
  e3.set(t, n >>> 0);
}
__name(dt, "dt");
function wt(e3, t) {
  e3.body = t;
}
__name(wt, "wt");
function lt(e3, t) {
  e3.headers = t;
}
__name(lt, "lt");
function pt(e3, t) {
  e3.headers = t;
}
__name(pt, "pt");
function xt(e3, t) {
  e3.highWaterMark = t;
}
__name(xt, "xt");
function yt(e3, t, n) {
  e3.method = b(t, n);
}
__name(yt, "yt");
function ht(e3, t) {
  e3.redirect = C[t];
}
__name(ht, "ht");
function mt(e3, t) {
  e3.status = t;
}
__name(mt, "mt");
function Rt(e3) {
  return e3.signal;
}
__name(Rt, "Rt");
function Ft(e3, t) {
  let n = t.stack, _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
  a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
}
__name(Ft, "Ft");
function St() {
  let e3 = typeof global > "u" ? null : global;
  return s(e3) ? 0 : g(e3);
}
__name(St, "St");
function Et() {
  let e3 = typeof globalThis > "u" ? null : globalThis;
  return s(e3) ? 0 : g(e3);
}
__name(Et, "Et");
function Ot() {
  let e3 = typeof self > "u" ? null : self;
  return s(e3) ? 0 : g(e3);
}
__name(Ot, "Ot");
function It() {
  let e3 = typeof window > "u" ? null : window;
  return s(e3) ? 0 : g(e3);
}
__name(It, "It");
function kt(e3) {
  return e3.status;
}
__name(kt, "kt");
function Tt(e3, t, n) {
  return e3.then(t, n);
}
__name(Tt, "Tt");
function zt(e3, t) {
  return e3.then(t);
}
__name(zt, "zt");
function Mt(e3) {
  return e3.toString();
}
__name(Mt, "Mt");
function jt(e3, t) {
  let n = t.url, _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
  a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
}
__name(jt, "jt");
function At(e3) {
  return e3.value;
}
__name(At, "At");
function Lt(e3) {
  let t = e3.view;
  return s(t) ? 0 : g(t);
}
__name(Lt, "Lt");
function qt() {
  return c(function(e3) {
    let t = e3.webSocket;
    return s(t) ? 0 : g(t);
  }, arguments);
}
__name(qt, "qt");
function Dt(e3) {
  let t = e3.original;
  return t.cnt-- == 1 ? (t.a = 0, true) : false;
}
__name(Dt, "Dt");
function Ct(e3, t, n) {
  return X(e3, t, 324, H);
}
__name(Ct, "Ct");
function Ut(e3, t) {
  let n = I(t), _ = l(n, r.__wbindgen_malloc, r.__wbindgen_realloc), o = d;
  a().setInt32(e3 + 4 * 1, o, true), a().setInt32(e3 + 4 * 0, _, true);
}
__name(Ut, "Ut");
function Wt() {
  let e3 = r.__wbindgen_export_4, t = e3.grow(4);
  e3.set(0, void 0), e3.set(t + 0, void 0), e3.set(t + 1, null), e3.set(t + 2, true), e3.set(t + 3, false);
}
__name(Wt, "Wt");
function Bt(e3) {
  return typeof e3 == "function";
}
__name(Bt, "Bt");
function Pt(e3) {
  return typeof e3 == "string";
}
__name(Pt, "Pt");
function $t(e3) {
  return e3 === void 0;
}
__name($t, "$t");
function Nt() {
  return r.memory;
}
__name(Nt, "Nt");
function Vt(e3) {
  return e3;
}
__name(Vt, "Vt");
function Xt(e3, t) {
  let n = t, _ = typeof n == "string" ? n : void 0;
  var o = s(_) ? 0 : l(_, r.__wbindgen_malloc, r.__wbindgen_realloc), f = d;
  a().setInt32(e3 + 4 * 1, f, true), a().setInt32(e3 + 4 * 0, o, true);
}
__name(Xt, "Xt");
function Gt(e3, t) {
  return b(e3, t);
}
__name(Gt, "Gt");
function Ht(e3, t) {
  throw new Error(b(e3, t));
}
__name(Ht, "Ht");
var U = new WebAssembly.Instance(Jt, { "./index_bg.js": w });
M(U.exports);
U.exports.__wbindgen_start?.();
var E = class extends Yt {
  static {
    __name(this, "E");
  }
  async fetch(t) {
    return await j(t, this.env, this.ctx);
  }
  async queue(t) {
    return await (void 0)(t, this.env, this.ctx);
  }
  async scheduled(t) {
    return await (void 0)(t, this.env, this.ctx);
  }
};
var vt = ["IntoUnderlyingByteSource", "IntoUnderlyingSink", "IntoUnderlyingSource", "MinifyConfig", "PolishConfig", "R2Range", "RequestRedirect", "fetch", "queue", "scheduled", "getMemory"];
Object.keys(w).map((e3) => {
  vt.includes(e3) | e3.startsWith("__") || (E.prototype[e3] = w[e3]);
});
var en = E;

// node_modules/wrangler/templates/middleware/middleware-ensure-req-body-drained.ts
var drainBody = /* @__PURE__ */ __name(async (request, env, _ctx, middlewareCtx) => {
  try {
    return await middlewareCtx.next(request, env);
  } finally {
    try {
      if (request.body !== null && !request.bodyUsed) {
        const reader = request.body.getReader();
        while (!(await reader.read()).done) {
        }
      }
    } catch (e3) {
      console.error("Failed to drain the unused request body.", e3);
    }
  }
}, "drainBody");
var middleware_ensure_req_body_drained_default = drainBody;

// node_modules/wrangler/templates/middleware/middleware-miniflare3-json-error.ts
function reduceError(e3) {
  return {
    name: e3?.name,
    message: e3?.message ?? String(e3),
    stack: e3?.stack,
    cause: e3?.cause === void 0 ? void 0 : reduceError(e3.cause)
  };
}
__name(reduceError, "reduceError");
var jsonError = /* @__PURE__ */ __name(async (request, env, _ctx, middlewareCtx) => {
  try {
    return await middlewareCtx.next(request, env);
  } catch (e3) {
    const error = reduceError(e3);
    return Response.json(error, {
      status: 500,
      headers: { "MF-Experimental-Error-Stack": "true" }
    });
  }
}, "jsonError");
var middleware_miniflare3_json_error_default = jsonError;

// .wrangler/tmp/bundle-NPuAeG/middleware-insertion-facade.js
var __INTERNAL_WRANGLER_MIDDLEWARE__ = [
  middleware_ensure_req_body_drained_default,
  middleware_miniflare3_json_error_default
];
var middleware_insertion_facade_default = en;

// node_modules/wrangler/templates/middleware/common.ts
var __facade_middleware__ = [];
function __facade_register__(...args) {
  __facade_middleware__.push(...args.flat());
}
__name(__facade_register__, "__facade_register__");
function __facade_invokeChain__(request, env, ctx, dispatch, middlewareChain) {
  const [head, ...tail] = middlewareChain;
  const middlewareCtx = {
    dispatch,
    next(newRequest, newEnv) {
      return __facade_invokeChain__(newRequest, newEnv, ctx, dispatch, tail);
    }
  };
  return head(request, env, ctx, middlewareCtx);
}
__name(__facade_invokeChain__, "__facade_invokeChain__");
function __facade_invoke__(request, env, ctx, dispatch, finalMiddleware) {
  return __facade_invokeChain__(request, env, ctx, dispatch, [
    ...__facade_middleware__,
    finalMiddleware
  ]);
}
__name(__facade_invoke__, "__facade_invoke__");

// .wrangler/tmp/bundle-NPuAeG/middleware-loader.entry.ts
var __Facade_ScheduledController__ = class ___Facade_ScheduledController__ {
  constructor(scheduledTime, cron, noRetry) {
    this.scheduledTime = scheduledTime;
    this.cron = cron;
    this.#noRetry = noRetry;
  }
  static {
    __name(this, "__Facade_ScheduledController__");
  }
  #noRetry;
  noRetry() {
    if (!(this instanceof ___Facade_ScheduledController__)) {
      throw new TypeError("Illegal invocation");
    }
    this.#noRetry();
  }
};
function wrapExportedHandler(worker) {
  if (__INTERNAL_WRANGLER_MIDDLEWARE__ === void 0 || __INTERNAL_WRANGLER_MIDDLEWARE__.length === 0) {
    return worker;
  }
  for (const middleware of __INTERNAL_WRANGLER_MIDDLEWARE__) {
    __facade_register__(middleware);
  }
  const fetchDispatcher = /* @__PURE__ */ __name(function(request, env, ctx) {
    if (worker.fetch === void 0) {
      throw new Error("Handler does not export a fetch() function.");
    }
    return worker.fetch(request, env, ctx);
  }, "fetchDispatcher");
  return {
    ...worker,
    fetch(request, env, ctx) {
      const dispatcher = /* @__PURE__ */ __name(function(type, init) {
        if (type === "scheduled" && worker.scheduled !== void 0) {
          const controller = new __Facade_ScheduledController__(
            Date.now(),
            init.cron ?? "",
            () => {
            }
          );
          return worker.scheduled(controller, env, ctx);
        }
      }, "dispatcher");
      return __facade_invoke__(request, env, ctx, dispatcher, fetchDispatcher);
    }
  };
}
__name(wrapExportedHandler, "wrapExportedHandler");
function wrapWorkerEntrypoint(klass) {
  if (__INTERNAL_WRANGLER_MIDDLEWARE__ === void 0 || __INTERNAL_WRANGLER_MIDDLEWARE__.length === 0) {
    return klass;
  }
  for (const middleware of __INTERNAL_WRANGLER_MIDDLEWARE__) {
    __facade_register__(middleware);
  }
  return class extends klass {
    #fetchDispatcher = /* @__PURE__ */ __name((request, env, ctx) => {
      this.env = env;
      this.ctx = ctx;
      if (super.fetch === void 0) {
        throw new Error("Entrypoint class does not define a fetch() function.");
      }
      return super.fetch(request);
    }, "#fetchDispatcher");
    #dispatcher = /* @__PURE__ */ __name((type, init) => {
      if (type === "scheduled" && super.scheduled !== void 0) {
        const controller = new __Facade_ScheduledController__(
          Date.now(),
          init.cron ?? "",
          () => {
          }
        );
        return super.scheduled(controller);
      }
    }, "#dispatcher");
    fetch(request) {
      return __facade_invoke__(
        request,
        this.env,
        this.ctx,
        this.#dispatcher,
        this.#fetchDispatcher
      );
    }
  };
}
__name(wrapWorkerEntrypoint, "wrapWorkerEntrypoint");
var WRAPPED_ENTRY;
if (typeof middleware_insertion_facade_default === "object") {
  WRAPPED_ENTRY = wrapExportedHandler(middleware_insertion_facade_default);
} else if (typeof middleware_insertion_facade_default === "function") {
  WRAPPED_ENTRY = wrapWorkerEntrypoint(middleware_insertion_facade_default);
}
var middleware_loader_entry_default = WRAPPED_ENTRY;
export {
  k as IntoUnderlyingByteSource,
  T as IntoUnderlyingSink,
  F as IntoUnderlyingSource,
  S as MinifyConfig,
  Y as PolishConfig,
  z as R2Range,
  v as RequestRedirect,
  __INTERNAL_WRANGLER_MIDDLEWARE__,
  te as __wbg_Error_0497d5bdba9362e5,
  ne as __wbg_String_8f0eb39a4a4c2f66,
  re as __wbg_append_0342728346e47425,
  _e as __wbg_body_3ee5f3b57855c324,
  oe as __wbg_body_e1e045c770257634,
  ce as __wbg_buffer_a1a27a0dfa70165d,
  ie as __wbg_buffer_e495ba54cee589cc,
  se as __wbg_byobRequest_56aa768ee4dfed17,
  ue as __wbg_byteLength_937f8a52f9697148,
  fe as __wbg_byteOffset_4d94b7170e641898,
  ae as __wbg_call_f2db6205e5c51dc8,
  be as __wbg_call_fbe8be8bf6436ce5,
  ge as __wbg_cancel_4d78160f447bbbeb,
  de as __wbg_catch_b51fce253ee18ec3,
  we as __wbg_cause_af6ef82a8abe435b,
  le as __wbg_cf_475e858e5c5db972,
  pe as __wbg_cf_60aafe7bb03e919a,
  xe as __wbg_close_290fb040af98d3ac,
  ye as __wbg_close_b2641ef0870e518c,
  he as __wbg_constructor_1a4f07ad72d5cac3,
  me as __wbg_done_4d01f352bade43b7,
  Re as __wbg_enqueue_a62faa171c4fd287,
  Fe as __wbg_entries_1532c722e9a3517c,
  Se as __wbg_error_51ecdd39ec054205,
  Ee as __wbg_error_7534b8e9a36f1ab4,
  Oe as __wbg_fetch_cd6e56bd3dd22dd0,
  Ie as __wbg_fetch_ed0fd2c8ad4bc3a3,
  ke as __wbg_getReader_48e00749fe3f6089,
  Te as __wbg_get_92470be87867c2e5,
  ze as __wbg_get_a131a44bd1eb6979,
  Me as __wbg_getdone_8355ddb2bc75c731,
  je as __wbg_getvalue_c1890a401d13f00b,
  Ae as __wbg_headers_0f0cbdc6290b6780,
  Le as __wbg_headers_67fbc7839fe933b3,
  qe as __wbg_httpProtocol_a32dd935f614e790,
  De as __wbg_instanceof_Error_58a92d81483a4b16,
  Ce as __wbg_instanceof_Response_e80ce8b7a2b968d2,
  Ue as __wbg_length_ab6d22b5ead75c72,
  We as __wbg_log_ea240990d83e374e,
  Be as __wbg_method_a3a2d7fac54c95f8,
  Pe as __wbg_minifyconfig_new,
  $e as __wbg_name_5503b7b8010787c5,
  Ne as __wbg_new_07b483f72211fd66,
  Ve as __wbg_new_476169e6d59f23ae,
  Xe as __wbg_new_4796e1cd2eb9ea6d,
  Ge as __wbg_new_8a6f238a6ece86ea,
  He as __wbg_new_a979b4b45bd55c7f,
  Je as __wbg_new_e30c39c06edaabf2,
  Ye as __wbg_new_e52b3efaaa774f96,
  ve as __wbg_newnoargs_ff528e72d35de39a,
  Ke as __wbg_newwithbyteoffsetandlength_3b01ecda099177e8,
  Qe as __wbg_newwithintounderlyingsource_b47f6a6a596a7f24,
  Ze as __wbg_newwithlength_08f872dc1e3ada2e,
  et as __wbg_newwithoptbuffersourceandinit_b77afe7366f846b5,
  tt as __wbg_newwithoptreadablestreamandinit_ce4ecbe22555867e,
  nt as __wbg_newwithoptstrandinit_8128e018ed06a4f8,
  rt as __wbg_next_e2da48d8fff7439a,
  _t as __wbg_queueMicrotask_46c1df247678729f,
  ot as __wbg_queueMicrotask_8acf3ccb75ed8d11,
  ct as __wbg_read_f4b89f69cc51efc7,
  it as __wbg_redirect_103cbb9748d5ac32,
  st as __wbg_releaseLock_c589dd51c0812aca,
  ut as __wbg_resolve_0dac8c580ffd4678,
  ft as __wbg_respond_b227f1c3be2bb879,
  at as __wbg_set_3f1d0b984ed272ed,
  bt as __wbg_set_c43293f93a35998a,
  gt as __wbg_set_d6bdfd275fb8a4ce,
  dt as __wbg_set_fe4e79d1ed3b0e9b,
  M as __wbg_set_wasm,
  wt as __wbg_setbody_971ec015fc13d6b4,
  lt as __wbg_setheaders_408564032a1382da,
  pt as __wbg_setheaders_65a4eb4c0443ae61,
  xt as __wbg_sethighwatermark_3017ad772d071dcb,
  yt as __wbg_setmethod_8ce1be0b4d701b7c,
  ht as __wbg_setredirect_562df6aa76f9dd5a,
  mt as __wbg_setstatus_bd5b448a903a8658,
  Rt as __wbg_signal_a393dc337ddce436,
  Ft as __wbg_stack_0ed75d68575b0f3c,
  St as __wbg_static_accessor_GLOBAL_487c52c58d65314d,
  Et as __wbg_static_accessor_GLOBAL_THIS_ee9704f328b6b291,
  Ot as __wbg_static_accessor_SELF_78c9e3071b912620,
  It as __wbg_static_accessor_WINDOW_a093d21393777366,
  kt as __wbg_status_a54682bbe52f9058,
  Tt as __wbg_then_82ab9fb4080f1707,
  zt as __wbg_then_db882932c0c714c6,
  Mt as __wbg_toString_21791a66666b3afd,
  jt as __wbg_url_f1c3162019331231,
  At as __wbg_value_17b896954e14f896,
  Lt as __wbg_view_a9ad80dcbad7cf1c,
  qt as __wbg_webSocket_38528fcd2e5cba7f,
  Dt as __wbindgen_cb_drop,
  Ct as __wbindgen_closure_wrapper1590,
  Ut as __wbindgen_debug_string,
  Wt as __wbindgen_init_externref_table,
  Bt as __wbindgen_is_function,
  Pt as __wbindgen_is_string,
  $t as __wbindgen_is_undefined,
  Nt as __wbindgen_memory,
  Vt as __wbindgen_number_new,
  Xt as __wbindgen_string_get,
  Gt as __wbindgen_string_new,
  Ht as __wbindgen_throw,
  middleware_loader_entry_default as default,
  j as fetch,
  G as start,
  Jt as wasmModule
};
//# sourceMappingURL=shim.js.map
