// ─────────────────────────────────────────────────────────────
//  Web pages for the Wi-Fi servo control, copied from
//  32_Servo_Controller_OV5640_UDP.ino (SETUP_HTML and CAMERA_HTML), with
//  ONE local addition to CAMERA_HTML, each part marked "SPILCD_SDCARD
//  addition": a THERMAL panel beside the LIVE FEED (.feeds / #thermal-*
//  CSS, the panel markup with its MIRROR/FLIP/ROT/ENHANCED toolbar, the
//  second <script> that polls /thermal and renders it) plus a small
//  resize fix so the camera panel stops at the thermal panel.
//  If the UDP page changes, re-copy it and re-apply those marked parts.
//
//  CAMERA_HTML is served at "/". LIVE FEED polls /capture (this board's
//  camera, JPEG); camera *settings* (/set) are accepted but ignored.
// ─────────────────────────────────────────────────────────────
#pragma once
#include <pgmspace.h>
static const char SETUP_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" type="image/x-icon" href="data:image/x-icon;base64,AAABAAMAEBAAAAEACABoBQAANgAAACAgEAABAAQA6AIAAJ4FAAAwMAAAAQAIAKgOAACGCAAAKAAAABAAAAAgAAAAAQAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAQAAAgEAAAEBAQACAQEAAgIAAAMCAAADAgEABAMAAAUEAgAGBAIABgUAAAcFAwAIBQMACAYAAAgGAwAJBwMACggAAA8MAAASDwAAExAAABkVAAAdGAAA++EAAPziAAD94wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAAAAAAAQgAAAAAAAAABAAGAQELEQAAAAAABQAABA0PGRkZGRkZGRkZGRkZDw0NDxkZGRgZGRkZGRkZGQ0NDQ8ZGRkPDQ0NDQ0NDQ0NDQ0PGRkZDw0NDQ0NDQ0NDQ0NDxkZGRAPDw8PDw0NDQ0NDQ8ZGRkZGRkZGRkZDw0NDQ0PGRkZGRkZGRkZGQ8NDQ0NDxkZGRAPDw8PDw0NDQ0NDQ8ZGRkPDQ0NDQ0NDQ0NDQ0PGRkZDw0NDQ0NDQ0NDQ0NDxgZGRkZGRcXGBgZGQ0NDQ8ZGRkZGRkZGRkYGRcPDQ0HFAIRERMGABIOFhUTAwoMAAAAAAAAAAAAAAAAAAAJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACgAAAAgAAAAQAAAAAEABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIBQMACAYDAAkHAwAKCAMACwkDAAwJAwANCgMADgoFABIPAgAUEAUAi30AAP3jAAAAAAAAAAAAAAAAAAAAAAAAAAS7u7u7u7u7u7u7u7tAAAAEqqqqqqqqqqqqqqqqQAAABLu7u7u7u7u7u7u7u0AAAASqqqqqqqqqqqqqqqowAAAEu7u7u7u7u7u7u7u7IAAABKqqqGVEREREREREMgAAAAS7u7YQAAAAAAAAAAAAAAAEqqqlAAAAAAAAAAAAAAAABLu7tAAAAAAAAAAAAAAAAASqqqQAAAAAAAAAAAAAAAAEu7u0AAAAAAAAAAAAAAAABKqqpQAAAAAAAAAAAAAAAAS7u7YQAAAAAAAAAAAAAAAEqqqoZURERERDIAAAAAAABLu7u7u7u7u7u7IAAAAAAASqqqqqqqqqqqqjAAAAAAAEu7u7u7u7u7u7swAAAAAABKqqqqqqqqqqqqIAAAAAAAS7u7hlREREREMgAAAAAAAEqqqmEAAAAAAAAAAAAAAABLu7tQAAAAAAAAAAAAAAAASqqqQAAAAAAAAAAAAAAAAEu7u0AAAAAAAAAAAAAAAABKqqpAAAAAAAAAAAAAAAAAS7u7UAAAAAAAAAAAAAAAAEqqqmEAAAAAAAAAAAAAAABLu7uGVEREREREREMgAAAASqqqqqqqqqqqqqqqogAAAEu7u7u7u7u7u7u7u7MAAABKqqqqqqqqqqqqqqqkAAAAS7u7u7u7u7u7u7u7tAAHd5qqqqqqqqqqqqqqqql3cAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACgAAAAwAAAAYAAAAAEACAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIBQMACAYDAAkHAwAKCAMACwkDAAwKAwANCgMADgoFAA0LAwAOCwMADwsFAA4MAwAPDQIAEAwFABANAgARDQUAEQ8CABIPAgATDgUAEw8CABMPBQAUEAUAFhIFABcTBQAYFAUAGhUFABoWAgAaFgUAHBcEAB0YBAAfGwQAIBsEACEcBAAiHAQAinwAAIt9AAD74QAA/OIAAP3jAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgUOEBETExMTExMTExMTExMTExMTExMTExMTExMTExEQDgUCAAAAAAAABwcHBwcKFCQlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSQUCgcHBwcHBwcHBwcKFyUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHAAAAAAABCCIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyIIAQAAAAAAAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyILAgAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUYCgcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHAAAAAAACCyIjIyMjIyIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIDAAAAAAAAAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwsLCwsLCwsJBgMBAAAAAAAABwcHBwcNGSUmJiYmJR8VDw0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQoKCgcHBwcHBwcHBwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRsNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIhEEAgICAgICAgICAgICAgICAQEBAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwkGAwEAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJiUlJSUlJSUlJSUlJSUlJSUlJSUlJBIHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJRcKBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIggBAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIggBAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJRcKBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJiUlJSUlJSUlJSUlJSUlJSUlJSUlJBIHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwkGAwEAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIhEEAgICAgICAgICAgICAgICAQEBAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRsNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJR8VDw0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQoKCgcHBwcHBwcHAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwsLCwsLCwsJBgMBAAAAAAAAAAAAAAACCyIjIyMjIyIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIDAAAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUYCgcHBwcHAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyILAgAAAAAAAAAAAAABCCIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyIIAQAAAAAABwcHBwcKFyUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHBwcHBwcKFCQlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSQUCgcHBwcHBwcHBwcHDRYdHiAhISEhISEhISEhISEhISEhISEhISEhISEhISAeHRYNBwcHBwcHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA">
  <title>32 Servo Controller - Setup</title>
  <style>
    *{box-sizing:border-box;margin:0;padding:0}
    :root{--bg:#050709;--accent:#00ffe7;--accent2:#ff3c5f;--text:#b8d8e8;--dim:#3a5060;--danger:#ff3c5f}
    html,body{
      min-height:100vh;background:var(--bg);color:var(--text);
      font-family:'Orbitron',monospace;
      display:flex;flex-direction:column;align-items:center;justify-content:center;padding:20px;gap:20px;
    }
    body::before{
      content:'';position:fixed;inset:0;
      background-image:linear-gradient(rgba(0,255,231,0.05) 1px,transparent 1px),
        linear-gradient(90deg,rgba(0,255,231,0.05) 1px,transparent 1px);
      background-size:48px 48px;pointer-events:none;z-index:0;
    }
    body::after{
      content:'';position:fixed;inset:0;
      background:repeating-linear-gradient(0deg,transparent,transparent 3px,rgba(0,0,0,0.08) 3px,rgba(0,0,0,0.08) 4px);
      pointer-events:none;z-index:0;
    }
    @keyframes statglow-cyan{
      0%,100%{text-shadow:-2px 0 rgba(0,255,231,.45),2px 0 rgba(255,60,95,.45),0 0 10px rgba(0,255,231,.8),0 0 24px rgba(0,255,231,.4)}
      50%{text-shadow:-4px 0 rgba(0,255,231,.7),4px 0 rgba(255,60,95,.7),0 0 22px rgba(0,255,231,1),0 0 44px rgba(0,255,231,.5)}
    }
    @keyframes statglow-pink{
      0%,100%{text-shadow:2px 0 rgba(255,60,95,.45),-2px 0 rgba(0,255,231,.45),0 0 10px rgba(255,60,95,.7),0 0 24px rgba(255,60,95,.3)}
      50%{text-shadow:4px 0 rgba(255,60,95,.7),-4px 0 rgba(0,255,231,.7),0 0 22px rgba(255,60,95,1),0 0 44px rgba(255,60,95,.5)}
    }
    @keyframes logo-flicker{0%,90%,92%,97%,97.5%,100%{opacity:1}91.4%{opacity:.12}97.2%{opacity:.55}}
    @keyframes pulseline{0%,100%{opacity:.9}50%{opacity:.2}}
    @keyframes fadeInUp{from{opacity:0;transform:translateY(12px)}to{opacity:1;transform:none}}
    .logo-wrap{text-align:center;position:relative;z-index:1}
    .logo{font-size:1.2rem;font-weight:800;letter-spacing:4px;text-transform:uppercase}
    .logo-real{color:var(--accent);animation:statglow-cyan 2.5s ease-in-out infinite,logo-flicker 8s ease-in-out infinite}
    .logo-driver{color:var(--accent2);animation:statglow-pink 2.5s ease-in-out infinite,logo-flicker 8s ease-in-out infinite .3s}
    .logo-subtitle{font-family:'Share Tech Mono',monospace;font-size:9px;letter-spacing:3px;color:var(--accent);margin-top:4px}
    .login-box{
      width:340px;max-width:95vw;background:rgba(5,10,16,0.85);
      padding:28px 24px;position:relative;
      animation:fadeInUp .5s .1s ease both;
      backdrop-filter:blur(8px);z-index:1;
    }
    .login-box::before{
      content:'';position:absolute;top:0;left:0;right:0;height:2px;
      background:linear-gradient(90deg,transparent,var(--accent),var(--accent2),var(--accent),transparent);
      animation:pulseline 2s ease-in-out infinite;
    }
    .corner-tl,.corner-tr,.corner-bl,.corner-br{position:absolute;width:12px;height:12px}
    .corner-tl{top:0;left:0;border-top:1.5px solid var(--accent);border-left:1.5px solid var(--accent)}
    .corner-tr{top:0;right:0;border-top:1.5px solid var(--accent);border-right:1.5px solid var(--accent)}
    .corner-bl{bottom:0;left:0;border-bottom:1.5px solid var(--accent2);border-left:1.5px solid var(--accent2)}
    .corner-br{bottom:0;right:0;border-bottom:1.5px solid var(--accent2);border-right:1.5px solid var(--accent2)}
    .field-wrap{margin-bottom:14px}
    .field-label{font-size:.6rem;letter-spacing:3px;color:var(--dim);text-transform:uppercase;margin-bottom:6px;font-family:'Share Tech Mono',monospace}
    input[type=text],input[type=password]{
      width:100%;background:rgba(0,20,30,0.75);
      border:1px solid rgba(0,255,231,0.3);color:var(--accent);
      font-family:'Share Tech Mono',monospace;font-size:.8rem;
      padding:10px 14px;outline:none;transition:border-color .2s,background .2s;
    }
    input[type=text]::placeholder,input[type=password]::placeholder{color:var(--dim);opacity:.7}
    input[type=text]:focus,input[type=password]:focus{border-color:rgba(0,255,231,.85);background:rgba(0,30,45,.82)}
    .pw-wrap{position:relative}
    .pw-wrap input{padding-right:44px}
    .eye{position:absolute;right:12px;top:50%;transform:translateY(-50%);cursor:pointer;color:var(--dim);font-size:1.1rem;user-select:none}
    .scan-row{display:flex;gap:8px;align-items:stretch}
    .ssid-dropdown{position:relative;font-family:'Share Tech Mono',monospace;flex:1;z-index:100}
    .ssid-trigger{
      display:flex;align-items:center;justify-content:space-between;gap:8px;
      background:rgba(0,20,30,0.75);border:1px solid rgba(0,255,231,0.3);color:var(--accent);
      padding:10px 14px;cursor:pointer;font-size:.7rem;font-weight:700;
      letter-spacing:.08em;text-transform:uppercase;white-space:nowrap;user-select:none;width:100%;
      transition:border-color .2s;
    }
    .ssid-trigger:hover{border-color:var(--accent)}
    .ssid-arrow{font-size:.65rem;transition:transform .25s;flex-shrink:0}
    .ssid-dropdown.open .ssid-arrow{transform:rotate(180deg)}
    .ssid-menu{
      display:none;position:absolute;top:calc(100% + 4px);left:0;
      list-style:none;padding:4px 0;margin:0;
      background:#050d14;border:1px solid rgba(0,255,231,0.2);
      min-width:100%;max-height:200px;overflow-y:auto;
      box-shadow:0 0 20px rgba(0,255,231,.12),0 8px 32px #000c;
    }
    .ssid-dropdown.open .ssid-menu{display:block}
    .ssid-menu li{
      display:flex;justify-content:space-between;align-items:center;gap:12px;
      padding:9px 14px;color:var(--text);font-size:.74rem;
      letter-spacing:.06em;text-transform:uppercase;cursor:pointer;
      border-left:2px solid transparent;transition:background .1s,color .1s,border-color .1s;
    }
    .ssid-menu li span{color:var(--dim);font-size:.7rem}
    .ssid-menu li:hover{background:rgba(0,255,231,.06);color:var(--accent);border-left-color:var(--accent)}
    .ssid-placeholder{color:var(--dim)!important;cursor:default!important;font-size:.7rem!important;text-transform:none!important;letter-spacing:.04em!important}
    .ssid-placeholder:hover{background:transparent!important;border-left-color:transparent!important;color:var(--dim)!important}
    .btn-scan{
      background:rgba(0,20,30,0.75);border:1px solid rgba(0,255,231,0.25);color:var(--dim);
      padding:10px 14px;cursor:pointer;font-size:.6rem;font-family:'Orbitron',monospace;
      letter-spacing:2px;text-transform:uppercase;white-space:nowrap;
      transition:border-color .2s,color .2s;flex-shrink:0;
    }
    .btn-scan:hover{border-color:var(--accent);color:var(--accent)}
    .btn-connect{
      margin-top:8px;width:100%;background:rgba(0,20,30,0.75);color:var(--accent);
      border:1px solid rgba(0,255,231,.4);padding:12px;
      font-size:.75rem;font-family:'Share Tech Mono',monospace;
      letter-spacing:3px;text-transform:uppercase;cursor:pointer;
      transition:background .2s,box-shadow .2s,border-color .2s;backdrop-filter:blur(4px);
    }
    .btn-connect:hover{background:rgba(0,40,55,.88);box-shadow:0 0 12px rgba(0,255,231,.25);border-color:var(--accent)}
    .btn-reset{
      margin-top:8px;width:100%;background:rgba(40,0,10,0.55);color:var(--danger);
      border:1px solid rgba(255,60,95,.4);padding:11px;
      font-size:.7rem;font-family:'Share Tech Mono',monospace;
      letter-spacing:3px;text-transform:uppercase;cursor:pointer;
      transition:background .2s,box-shadow .2s,border-color .2s;backdrop-filter:blur(4px);
    }
    .btn-reset:hover{background:rgba(70,0,18,.8);box-shadow:0 0 12px rgba(255,60,95,.3);border-color:var(--danger)}
    #msg{margin-top:12px;text-align:center;font-size:.72rem;font-family:'Share Tech Mono',monospace;min-height:18px;letter-spacing:1px}
    .ok{color:var(--accent)}.err{color:var(--danger)}
    .spinner{display:inline-block;width:12px;height:12px;border:2px solid rgba(0,255,231,.15);
             border-top-color:var(--accent);border-radius:50%;animation:spin .7s linear infinite;vertical-align:middle;margin-right:6px}
    @keyframes spin{to{transform:rotate(360deg)}}
  </style>
</head>
<body>
<div class="logo-wrap">
  <div class="logo"><span class="logo-real">32 SERVO</span><span class="logo-driver"> CONTROLLER</span></div>
  <div class="logo-subtitle">&#9658;&nbsp;&nbsp;WIFI SETUP&nbsp;&nbsp;&#9668;</div>
</div>

<div class="login-box">
  <div class="corner-tl"></div><div class="corner-tr"></div>
  <div class="corner-bl"></div><div class="corner-br"></div>

  <div class="field-wrap">
    <div class="field-label"><span style="color:var(--accent2)">//</span><span style="color:var(--accent)"> NETWORK (SSID)</span></div>
    <div class="scan-row">
      <div class="ssid-dropdown" id="ssid-dropdown">
        <div class="ssid-trigger" id="ssid-trigger" onclick="toggleSsidDropdown()">
          <span id="ssid-label">tap Scan to find networks</span>
          <span class="ssid-arrow">&#9660;</span>
        </div>
        <ul class="ssid-menu" id="ssid-menu">
          <li class="ssid-placeholder">tap Scan to find networks</li>
        </ul>
      </div>
      <button type="button" class="btn-scan" onclick="scanNetworks()">SCAN</button>
    </div>
  </div>

  <div class="field-wrap">
    <div class="field-label"><span style="color:var(--accent2)">//</span><span style="color:var(--accent)"> SSID</span></div>
    <input type="text" id="ssid" placeholder="SSID" autocomplete="off" spellcheck="false">
  </div>

  <div class="field-wrap">
    <div class="field-label"><span style="color:var(--accent2)">//</span><span style="color:var(--accent)"> PASSWORD</span></div>
    <div class="pw-wrap">
      <input type="password" id="pass" placeholder="PASSWORD" autocomplete="new-password">
      <span class="eye" onclick="togglePw()">&#128065;</span>
    </div>
  </div>

  <button type="button" class="btn-connect" onclick="doConnect()">[ CONNECT &amp; SAVE ]</button>
  <button type="button" class="btn-reset" onclick="resetWifi()">&#9888; RESET WIFI TO DEFAULT</button>
  <div id="msg"></div>

  <div style="text-align:center;margin-top:16px">
    <a href="/" style="font-family:'Share Tech Mono',monospace;font-size:9px;letter-spacing:3px;color:rgba(0,255,231,0.35);text-decoration:none;text-transform:uppercase">&#9664; BACK TO CONTROL</a>
  </div>
</div>
<script>
  function msg(text,cls){const e=document.getElementById('msg');e.innerHTML=text;e.className=cls||'';}
  function togglePw(){const p=document.getElementById('pass');p.type=p.type==='password'?'text':'password';}
  function pickSsid(v,label){
    if(v){
      document.getElementById('ssid').value=v;
      document.getElementById('ssid-label').textContent=label||v;
    }
    closeSsidDropdown();
  }
  function toggleSsidDropdown(){
    document.getElementById('ssid-dropdown').classList.toggle('open');
  }
  function closeSsidDropdown(){
    document.getElementById('ssid-dropdown').classList.remove('open');
  }
  document.addEventListener('click',function(e){
    const dd=document.getElementById('ssid-dropdown');
    if(!dd.contains(e.target))closeSsidDropdown();
  });
  function scanNetworks(){
    msg('<span class="spinner"></span>Scanning&hellip;');
    fetch('/scan').then(r=>r.json()).then(nets=>{
      const menu=document.getElementById('ssid-menu');
      menu.innerHTML='';
      if(nets.length===0){
        const li=document.createElement('li');
        li.className='ssid-placeholder';
        li.textContent='No networks found';
        menu.appendChild(li);
      } else {
        nets.forEach(n=>{
          const li=document.createElement('li');
          const label=n.ssid;
          const rssi=n.rssi+' dBm';
          li.innerHTML=label+'<span>'+rssi+'</span>';
          li.onclick=()=>pickSsid(n.ssid,n.ssid);
          menu.appendChild(li);
        });
      }
      document.getElementById('ssid-label').textContent='select a network';
      msg(nets.length+' networks found','ok');
    }).catch(()=>msg('Scan failed - try again','err'));
  }
  function doConnect(){
    const ssid=document.getElementById('ssid').value.trim();
    const pass=document.getElementById('pass').value;
    if(!ssid){msg('Please enter a network name (SSID)','err');return;}
    msg('<span class="spinner"></span>Saving &amp; connecting&hellip;');
    fetch('/save',{method:'POST',
      headers:{'Content-Type':'application/x-www-form-urlencoded'},
      body:'ssid='+encodeURIComponent(ssid)+'&pass='+encodeURIComponent(pass)
    }).then(r=>r.text()).then(t=>msg(t,'ok')).catch(()=>msg('Close this page and reconnect to WiFi','err'));
  }
  function resetWifi(){
    if(!confirm('Reset WiFi to default? This clears the saved network and reboots the board into its default Access Point setup mode.'))return;
    msg('<span class="spinner"></span>Resetting WiFi&hellip;');
    fetch('/forget').then(r=>r.text()).then(t=>msg(t,'ok'))
      .catch(()=>msg('Done — reconnect to the 32_SC setup network','ok'));
  }
  function setAPMode(){
    if(!confirm('Switch to Access Point mode? The device will reboot and broadcast its own WiFi network.'))return;
    msg('<span class="spinner"></span>Switching to AP mode&hellip;');
    fetch('/setap').then(r=>r.text()).then(t=>{
      msg(t,'ok');
    }).catch(()=>msg('Done — reconnect to 32_SC_Setup network','ok'));
  }
  window.addEventListener('DOMContentLoaded',scanNetworks);
  (function(){var l=document.createElement('link');l.rel='stylesheet';
  l.href='https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;800&family=Share+Tech+Mono&display=swap';
  document.head.appendChild(l);})();
</script>
</body>
</html>

)rawliteral";

static const char CAMERA_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>32 Servo Controller</title>
  <link rel="icon" type="image/x-icon" href="data:image/x-icon;base64,AAABAAMAEBAAAAEACABoBQAANgAAACAgEAABAAQA6AIAAJ4FAAAwMAAAAQAIAKgOAACGCAAAKAAAABAAAAAgAAAAAQAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAQAAAgEAAAEBAQACAQEAAgIAAAMCAAADAgEABAMAAAUEAgAGBAIABgUAAAcFAwAIBQMACAYAAAgGAwAJBwMACggAAA8MAAASDwAAExAAABkVAAAdGAAA++EAAPziAAD94wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAAAAAAAQgAAAAAAAAABAAGAQELEQAAAAAABQAABA0PGRkZGRkZGRkZGRkZDw0NDxkZGRgZGRkZGRkZGQ0NDQ8ZGRkPDQ0NDQ0NDQ0NDQ0PGRkZDw0NDQ0NDQ0NDQ0NDxkZGRAPDw8PDw0NDQ0NDQ8ZGRkZGRkZGRkZDw0NDQ0PGRkZGRkZGRkZGQ8NDQ0NDxkZGRAPDw8PDw0NDQ0NDQ8ZGRkPDQ0NDQ0NDQ0NDQ0PGRkZDw0NDQ0NDQ0NDQ0NDxgZGRkZGRcXGBgZGQ0NDQ8ZGRkZGRkZGRkYGRcPDQ0HFAIRERMGABIOFhUTAwoMAAAAAAAAAAAAAAAAAAAJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACgAAAAgAAAAQAAAAAEABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIBQMACAYDAAkHAwAKCAMACwkDAAwJAwANCgMADgoFABIPAgAUEAUAi30AAP3jAAAAAAAAAAAAAAAAAAAAAAAAAAS7u7u7u7u7u7u7u7tAAAAEqqqqqqqqqqqqqqqqQAAABLu7u7u7u7u7u7u7u0AAAASqqqqqqqqqqqqqqqowAAAEu7u7u7u7u7u7u7u7IAAABKqqqGVEREREREREMgAAAAS7u7YQAAAAAAAAAAAAAAAEqqqlAAAAAAAAAAAAAAAABLu7tAAAAAAAAAAAAAAAAASqqqQAAAAAAAAAAAAAAAAEu7u0AAAAAAAAAAAAAAAABKqqpQAAAAAAAAAAAAAAAAS7u7YQAAAAAAAAAAAAAAAEqqqoZURERERDIAAAAAAABLu7u7u7u7u7u7IAAAAAAASqqqqqqqqqqqqjAAAAAAAEu7u7u7u7u7u7swAAAAAABKqqqqqqqqqqqqIAAAAAAAS7u7hlREREREMgAAAAAAAEqqqmEAAAAAAAAAAAAAAABLu7tQAAAAAAAAAAAAAAAASqqqQAAAAAAAAAAAAAAAAEu7u0AAAAAAAAAAAAAAAABKqqpAAAAAAAAAAAAAAAAAS7u7UAAAAAAAAAAAAAAAAEqqqmEAAAAAAAAAAAAAAABLu7uGVEREREREREMgAAAASqqqqqqqqqqqqqqqogAAAEu7u7u7u7u7u7u7u7MAAABKqqqqqqqqqqqqqqqkAAAAS7u7u7u7u7u7u7u7tAAHd5qqqqqqqqqqqqqqqql3cAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACgAAAAwAAAAYAAAAAEACAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIBQMACAYDAAkHAwAKCAMACwkDAAwKAwANCgMADgoFAA0LAwAOCwMADwsFAA4MAwAPDQIAEAwFABANAgARDQUAEQ8CABIPAgATDgUAEw8CABMPBQAUEAUAFhIFABcTBQAYFAUAGhUFABoWAgAaFgUAHBcEAB0YBAAfGwQAIBsEACEcBAAiHAQAinwAAIt9AAD74QAA/OIAAP3jAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgUOEBETExMTExMTExMTExMTExMTExMTExMTExMTExEQDgUCAAAAAAAABwcHBwcKFCQlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSQUCgcHBwcHBwcHBwcKFyUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHAAAAAAABCCIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyIIAQAAAAAAAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyILAgAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUYCgcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHAAAAAAACCyIjIyMjIyIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIDAAAAAAAAAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwsLCwsLCwsJBgMBAAAAAAAABwcHBwcNGSUmJiYmJR8VDw0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQoKCgcHBwcHBwcHBwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRsNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIhEEAgICAgICAgICAgICAgICAQEBAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwkGAwEAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJiUlJSUlJSUlJSUlJSUlJSUlJSUlJBIHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJRcKBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIggBAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIggBAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJRcKBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJiUlJSUlJSUlJSUlJSUlJSUlJSUlJBIHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwkGAwEAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIhEEAgICAgICAgICAgICAgICAQEBAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRsNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJRkNBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCyIjIyMjIgsCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABwcHBwcNGSUmJiYmJRwPCgcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcHBwcNGSUmJiYmJR8VDw0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQoKCgcHBwcHBwcHAAAAAAACCyIjIyMjIhoQDAsLCwsLCwsLCwsLCwsLCwsLCwsLCwsJBgMBAAAAAAAAAAAAAAACCyIjIyMjIyIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIDAAAAAAAABwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHBwcHBwcNGSUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUYCgcHBwcHAAAAAAACCyIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyILAgAAAAAAAAAAAAABCCIjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyIIAQAAAAAABwcHBwcKFyUmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiYmJiUXCgcHBwcHBwcHBwcKFCQlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSUlJSQUCgcHBwcHBwcHBwcHDRYdHiAhISEhISEhISEhISEhISEhISEhISEhISEhISAeHRYNBwcHBwcHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA">
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;800&family=Share+Tech+Mono&display=swap" rel="stylesheet">
  <style>
    * { margin: 0; padding: 0; box-sizing: border-box; }
    ::-webkit-scrollbar { width: 14px; height: 14px; }
    ::-webkit-scrollbar-button { display: none; height: 0; width: 0; }
    ::-webkit-scrollbar-track { background: #0a0e14; border-left: 1px solid #0099bb22; }
    ::-webkit-scrollbar-thumb { background: #0099bb; border-radius: 0; box-shadow: 0 0 6px #0099bb, 0 0 12px #0099bb66; }
    ::-webkit-scrollbar-thumb:hover { background: #00e5ff; box-shadow: 0 0 8px #00e5ff, 0 0 18px #00e5ffaa; }
    ::-webkit-scrollbar-corner { background: #0a0e14; }
    :root {
      --bg: #050709; --accent: #00ffe7; --accent2: #ff3c5f; --accent3: #ffd600;
      --panel: rgba(8,16,28,0.92); --border: rgba(0,255,231,0.18);
      --text: #b8d8e8; --dim: #3a5060; --green: #00ff88; --blue: #4488ff;
    }
    html, body { width: 100%; height: 100%; background: var(--bg); color: var(--text);
      font-family: 'Orbitron', monospace; overflow: hidden; }
    #flat-ui { position: fixed; inset: 0; display: flex; flex-direction: column; z-index: 10; overflow: hidden; }
    #flat-ui::after { content: ''; position: absolute; inset: 0;
      background: repeating-linear-gradient(0deg, transparent, transparent 3px, rgba(0,0,0,0.06) 3px, rgba(0,0,0,0.06) 4px);
      pointer-events: none; z-index: 100; }
    #flat-ui::before { content: ''; position: fixed; inset: 0;
      background-image: linear-gradient(rgba(0,255,231,0.07) 1px, transparent 1px),
        linear-gradient(90deg, rgba(0,255,231,0.07) 1px, transparent 1px);
      background-size: 48px 48px; pointer-events: none; }
    /* HEADER */
    #header { display: flex; align-items: center; justify-content: space-between;
      padding: 12px 24px; min-height: 64px; border-bottom: 1px solid var(--border);
      background: var(--panel); position: relative; z-index: 5; flex-shrink: 0; }
    @keyframes statglow-cyan {
      0%,100% { text-shadow: -2px 0 rgba(0,255,231,0.45), 2px 0 rgba(255,60,95,0.45), 0 0 10px rgba(0,255,231,0.8), 0 0 24px rgba(0,255,231,0.4); }
      50%      { text-shadow: -4px 0 rgba(0,255,231,0.7), 4px 0 rgba(255,60,95,0.7), 0 0 22px rgba(0,255,231,1), 0 0 44px rgba(0,255,231,0.5); } }
    @keyframes statglow-pink {
      0%,100% { text-shadow: -2px 0 rgba(0,255,231,0.45), 2px 0 rgba(255,60,95,0.45), 0 0 10px rgba(255,60,95,0.8), 0 0 24px rgba(255,60,95,0.4); }
      50%      { text-shadow: -4px 0 rgba(0,255,231,0.7), 4px 0 rgba(255,60,95,0.7), 0 0 22px rgba(255,60,95,1), 0 0 44px rgba(255,60,95,0.5); } }
    @keyframes logo-flicker { 0%,90%,92%,97%,97.5%,100% { opacity: 1; } 91.4% { opacity: 0.12; } 97.2% { opacity: 0.55; } }
    .logo { font-size: 22px; font-weight: 800; letter-spacing: 4px; color: var(--accent); position: relative; }
    .logo-32sc { color: var(--accent); animation: statglow-cyan 2.5s ease-in-out infinite, logo-flicker 8s ease-in-out infinite; }
    .logo-cam  { color: var(--accent2); animation: statglow-pink 2.5s ease-in-out infinite, logo-flicker 8s ease-in-out infinite 0.3s; }
    .logo-subtitle { font-family: 'Share Tech Mono', monospace; font-size: 9px; letter-spacing: 3px;
      color: var(--accent); margin-top: 4px; text-align: center; }
    .dot { width: 7px; height: 7px; border-radius: 50%; background: var(--dim); }
    .dot.live { background: var(--accent); box-shadow: 0 0 8px var(--accent); animation: pulse 1.4s step-end infinite; }
    .dot.error { background: var(--accent2); box-shadow: 0 0 8px var(--accent2); }
    @keyframes pulse { 0%,49%{opacity:1} 50%,100%{opacity:0} }
    /* CALL SCREEN */
    #call-screen { padding: 16px 20px; gap: 14px; flex: 1; min-height: 0; overflow-y: auto;
      display: flex; flex-direction: column; }
    /* VIDEO */
    .video-wrap { flex: 0 0 auto; width: 100%; display: flex; flex-direction: column; }
    #video-panel { border: 1px solid var(--border); background: #000; position: relative;
      overflow: hidden; width: 100%; min-width: 160px; min-height: 240px; align-self: center; }
    #video-panel::before { content: ''; position: absolute; inset: 0;
      border: 1px solid rgba(0,255,231,0.08); pointer-events: none; z-index: 2; }
    #video-panel { position: relative; z-index: 101; }
    #stream { display: none; width: 100%; height: auto; }
    /* FULLSCREEN: maximize the video to fill the whole screen */
    #video-panel:fullscreen { width: 100vw; height: 100vh; min-height: 0; border: none;
      display: flex; align-items: center; justify-content: center; background: #000; }
    #video-panel:fullscreen #stream { width: 100%; height: 100%; object-fit: contain; }
    #video-panel:-webkit-full-screen { width: 100vw; height: 100vh; min-height: 0; border: none;
      display: flex; align-items: center; justify-content: center; background: #000; }
    #video-panel:-webkit-full-screen #stream { width: 100%; height: 100%; object-fit: contain; }
    #vid-fs { position: absolute; top: 6px; right: 8px; z-index: 6; cursor: pointer;
      width: 26px; height: 26px; display: flex; align-items: center; justify-content: center;
      background: rgba(4,8,15,0.55); border: 1px solid var(--border); border-radius: 4px;
      color: var(--accent); font-size: 13px; line-height: 1; transition: all .15s; }
    #vid-fs:hover { color: #fff; border-color: var(--accent); box-shadow: 0 0 8px var(--accent); }
    #vid-resize { position: absolute; bottom: 0; right: 0; width: 18px; height: 18px; z-index: 5; cursor: nwse-resize; touch-action: none; user-select: none; }
    #vid-resize::before { content: ''; position: absolute; bottom: 0; right: 0; width: 12px; height: 12px;
      border-right: 2px solid var(--accent2); border-bottom: 2px solid var(--accent2);
      opacity: 0.55; transition: opacity 0.2s; pointer-events: none; }
    #vid-resize:hover::before { opacity: 1; }
    .vid-label { position: absolute; top: 6px; left: 10px; font-family: 'Share Tech Mono', monospace;
      font-size: 9px; color: var(--accent); letter-spacing: 2px; z-index: 4; text-shadow: 0 0 8px var(--accent); }
    /* SPILCD_SDCARD addition: camera + thermal side by side (stacked on phones) */
    .feeds { display: grid; grid-template-columns: 1fr; gap: 10px; width: 100%; }
    @media (min-width: 820px) { .feeds { grid-template-columns: 3fr 2fr; align-items: start; } }
    .feeds #video-panel { align-self: start; }   /* top-align with the thermal panel */
    #thermal-panel { border: 1px solid var(--border); background: #000; position: relative;
      overflow: hidden; min-width: 160px; }
    #thermal-panel::before { content: ''; position: absolute; inset: 0;
      border: 1px solid rgba(255,60,95,0.10); pointer-events: none; z-index: 2; }
    #thermal-panel .vid-label { color: var(--accent2); text-shadow: 0 0 8px var(--accent2); }
    /* aspect-ratio of both follows the rotation (set from JS: 4/3 or 3/4) */
    #thermal-canvas { display: block; width: 100%; aspect-ratio: 4 / 3; image-rendering: auto; cursor: crosshair; }
    #thermal-status { position: absolute; inset: 0 0 auto 0; aspect-ratio: 4 / 3; display: flex;
      align-items: center; justify-content: center; text-align: center; padding: 0 12px;
      font-family: 'Share Tech Mono', monospace; font-size: 12px; letter-spacing: 0.25em;
      color: var(--accent2); background: rgba(4,8,15,0.72); z-index: 3; }
    #thermal-status.hidden { display: none; }
    #thermal-status.searching { color: #00ffcc99; animation: cs-blink 1s step-end infinite; }
    #thermal-scale { height: 6px; margin: 0 8px; border: 1px solid var(--border);
      background: linear-gradient(90deg,#000,#3c0078,#c8283c,#ffa000,#ffffdc); }
    #thermal-read { display: grid; grid-template-columns: repeat(4, 1fr); gap: 4px; padding: 6px 8px 8px; }
    .th-cell { display: flex; flex-direction: column; align-items: center; gap: 2px; }
    .th-lbl { font-family: 'Share Tech Mono', monospace; font-size: 8px; letter-spacing: 2px; color: var(--dim); }
    .th-val { font-family: 'Share Tech Mono', monospace; font-size: 13px; color: var(--text); }
    #thermal-tools { display: grid; grid-template-columns: repeat(4, 1fr); gap: 4px; padding: 0 8px 8px; }
    #thermal-tools .cam-toggle-btn { padding: 5px 2px; }
    #th-enh.on { border-color: var(--accent2); color: var(--accent2);
      background: rgba(255,60,95,0.08); box-shadow: 0 0 8px rgba(255,60,95,0.25); }
    #thermal-spot { position: absolute; z-index: 4; pointer-events: none; display: none;
      font-family: 'Share Tech Mono', monospace; font-size: 11px; color: #fff; padding: 1px 5px;
      background: rgba(4,8,15,0.8); border: 1px solid var(--accent); transform: translate(8px,-50%); }
    /* Calling spinner */
    #calling-spinner { display: flex; position: absolute; inset: 0; z-index: 10;
      flex-direction: column; align-items: center; justify-content: center; gap: 18px;
      background: rgba(4,8,15,0.72); }
    #calling-spinner.hidden { display: none; }
    .cs-ring { width: 80px; height: 80px; position: relative; }
    .cs-ring::before, .cs-ring::after { content: ''; position: absolute; border-radius: 50%; border: 3px solid transparent; }
    .cs-ring::before { inset: 0; border-top-color: #00ffcc; border-right-color: #00ffcc44;
      animation: cs-cw 1s linear infinite; filter: drop-shadow(0 0 6px #00ffcc); }
    .cs-ring::after  { inset: 12px; border-bottom-color: #ff003c; border-left-color: #ff003c44;
      animation: cs-cw 0.7s linear infinite reverse; filter: drop-shadow(0 0 6px #ff003c); }
    @keyframes cs-cw { to { transform: rotate(360deg); } }
    #calling-spinner .spinner-label { font-family: 'Share Tech Mono', monospace; font-size: 10px; letter-spacing: 0.3em;
      color: #00ffcc99; animation: cs-blink 1s step-end infinite; }
    @keyframes cs-blink { 50% { opacity: 0; } }
    /* No-camera state */
    #calling-spinner.no-cam .cs-ring { display: none; }
    #calling-spinner.no-cam .spinner-label { color: #ff3c5f; font-size: 12px; animation: none; opacity: 1; letter-spacing: 0.25em; }
    .vid-ctrl-disabled { opacity: 0.3; pointer-events: none; }
    /* HUD BAR */
    #hud { display: flex; align-items: center; gap: 8px; flex-wrap: wrap;
      border: 1px solid var(--border);
      background: rgba(5,10,16,0.95); padding: 7px 12px;
      position: relative; z-index: 200; }
    .hud-chip { display: flex; align-items: center; gap: 5px; padding: 4px 10px;
      border: 1px solid rgba(0,255,231,0.12); background: rgba(0,20,30,0.6);
      font-family: 'Share Tech Mono', monospace; font-size: 11px; color: var(--dim); white-space: nowrap; }
    .hud-val { color: var(--accent); font-weight: 700; min-width: 30px; text-align: right; font-family: 'Share Tech Mono', monospace; }
    .hud-val.ok   { color: var(--green); text-shadow: 0 0 6px var(--green); }
    .hud-val.warn { color: var(--accent3); }
    .hud-unit { font-size: 9px; color: var(--dim); letter-spacing: 1px; }
    .tp-wrap { flex: 1; min-width: 60px; max-width: 120px; height: 4px;
      background: rgba(0,255,231,0.08); border: 1px solid rgba(0,255,231,0.12); }
    .tp-fill { height: 100%; width: 0%; background: var(--green);
      box-shadow: 0 0 4px var(--green); transition: width 0.6s ease, background 0.4s; }
    .hud-spacer { flex: 1; min-width: 8px; }
    /* CTRL BUTTONS */
    .ctrl-btn { font-family: 'Orbitron', monospace; font-size: 9px; font-weight: 600;
      letter-spacing: 2px; padding: 9px 8px; background: rgba(0,20,30,0.75);
      border: 1px solid var(--border); color: var(--accent); cursor: pointer; border-radius: 0;
      transition: all 0.2s; text-transform: uppercase; white-space: nowrap; backdrop-filter: blur(4px); }
    .ctrl-btn:hover:not(:disabled) { border-color: var(--accent); color: var(--accent); }
    .ctrl-btn.btn-danger { color: var(--accent2); border-color: var(--accent2); background: rgba(30,8,14,0.75);
      border-radius: 4px; font-size: 10px; font-weight: 600; padding: 7px 14px; }
    .ctrl-btn.btn-danger:hover:not(:disabled) { background: rgba(50,10,20,0.88); box-shadow: 0 0 12px rgba(255,60,95,0.25); }
    /* COLLAPSIBLE PANELS — exact realdriver style */
    #ctrl-wrap, #servo-wrap { flex-shrink: 0; position: relative; }
    #ctrl-header, #servo-header { display: flex; justify-content: space-between; align-items: center;
      padding: 6px 12px; border: 1px solid var(--border); background: rgba(5,10,16,0.80);
      cursor: pointer; font-family: 'Share Tech Mono', monospace; font-size: 10px;
      color: var(--accent); letter-spacing: 2px; backdrop-filter: blur(6px); }
    #ctrl-body, #servo-body { border: 1px solid var(--border); border-top: none;
      background: rgba(5,10,16,0.72); padding: 12px; backdrop-filter: blur(6px); display: none; }
    /* GAMEPAD STATUS */
    #gp-status-bar { display: flex; align-items: center; justify-content: center;
      padding: 4px 0; margin-bottom: 6px; font-family: 'Share Tech Mono', monospace; font-size: 10px; }
    #gp-status { color: var(--dim); text-align: center; }
    #gp-live-badge { display: none; font-size: 9px; letter-spacing: 2px;
      padding: 2px 8px; border: 1px solid var(--accent); color: var(--accent); }
    /* MAP SECTIONS */
    .map-section { margin-bottom: 10px; }
    .map-section-header { display: flex; justify-content: space-between; align-items: center;
      padding: 4px 0; margin-bottom: 6px; border-bottom: 1px solid rgba(0,255,231,0.1); }
    .map-section-label { font-family: 'Share Tech Mono', monospace; font-size: 9px; letter-spacing: 3px; text-transform: uppercase; }
    .map-add-btn { font-family: 'Share Tech Mono', monospace; font-size: 9px; letter-spacing: 1px;
      padding: 3px 10px; width: 120px; text-align: center;
      background: rgba(0,20,30,0.75); border: 1px solid rgba(0,255,231,0.3); color: var(--accent);
      cursor: pointer; transition: all 0.2s; text-transform: uppercase; backdrop-filter: blur(4px); }
    .map-add-btn:hover { border-color: var(--accent); color: var(--accent); }
    /* MAPPING ROWS */
    .mapping-row { display: grid; gap: 5px; align-items: center;
      background: rgba(0,0,0,0.35); border: 1px solid rgba(0,255,231,0.1);
      padding: 5px 8px; margin-bottom: 5px; overflow: visible; }
    .mapping-row.axis-row   { grid-template-columns: 1fr 1fr auto auto auto; }
    .mapping-row.button-row { grid-template-columns: 1fr 1fr 1fr auto; }
    .mapping-row.button-row.has-val { grid-template-columns: 1fr 1fr 1fr 60px auto; }
    .mapping-row.key-row { grid-template-columns: 80px 1fr 1fr auto; }
    .mapping-row.key-row.has-val { grid-template-columns: 80px 1fr 1fr 60px auto; }
    .key-cap-btn { background: rgba(0,20,30,0.75); border: 1px solid rgba(0,255,231,0.3);
      color: var(--accent); font-family: 'Share Tech Mono', monospace; font-size: 9px;
      letter-spacing: 1px; padding: 6px 6px; cursor: pointer; width: 100%;
      text-align: center; transition: border-color 0.2s; white-space: nowrap;
      overflow: hidden; text-overflow: ellipsis; }
    .key-cap-btn:hover { border-color: var(--accent); }
    .key-cap-btn.capturing { border-color: var(--accent2); color: var(--accent2);
      animation: rec-blink 0.7s ease-in-out infinite; }
    .map-select { appearance: none; -webkit-appearance: none;
      background: rgba(0,20,30,0.75) url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='8' height='8' viewBox='0 0 8 8'%3E%3Cpath fill='%2300ffe7' d='M0 2l4 4 4-4z'/%3E%3C/svg%3E") no-repeat right 8px center;
      border: 1px solid rgba(0,255,231,0.3); color: var(--accent);
      font-family: 'Share Tech Mono', monospace; font-size: 9px;
      padding: 6px 24px 6px 8px; outline: none; transition: border-color 0.2s, background-color 0.2s;
      width: 100%; backdrop-filter: blur(4px); letter-spacing: 1px; cursor: pointer; }
    .map-select:hover { border-color: var(--accent); }
    .map-select:focus { border-color: rgba(0,255,231,0.85); background-color: rgba(0,30,45,0.82); outline: none; }
    .map-select option { background: #050a12; color: var(--accent); }
    /* Custom stepper */
    .custom-stepper { display: flex; align-items: stretch; box-sizing: border-box;
      border: 1px solid rgba(0,255,231,0.2); background: rgba(0,10,18,0.85); height: 26px; }
    .custom-stepper .stepper-input { flex: 1; min-width: 0; background: transparent; border: none;
      color: var(--accent); font-family: 'Share Tech Mono', monospace; font-size: 9px;
      text-align: center; outline: none; padding: 0 3px; }
    .custom-stepper .stepper-btns { display: flex; flex-direction: column; flex-shrink: 0;
      border-left: 1px solid rgba(0,255,231,0.15); width: 18px; }
    .custom-stepper .stepper-btn { flex: 1; background: transparent; border: none;
      color: rgba(0,255,231,0.6); cursor: pointer; padding: 0; font-size: 7px; line-height: 1;
      display: flex; align-items: center; justify-content: center; transition: background 0.1s, color 0.1s; }
    .custom-stepper .stepper-btn:first-child { border-bottom: 1px solid rgba(0,255,231,0.12); }
    .custom-stepper .stepper-btn:hover { background: rgba(0,255,231,0.12); color: var(--accent); }
    .dz-stepper { width: 68px; }
    .map-val-stepper { width: 100%; }
    /* Custom checkbox */
    .map-check-label { display: flex; align-items: center; gap: 4px;
      font-family: 'Share Tech Mono', monospace; font-size: 9px;
      color: var(--accent); white-space: nowrap; cursor: pointer; }
    .map-check-label input[type="checkbox"] { appearance: none; -webkit-appearance: none;
      width: 11px; height: 11px; flex-shrink: 0; background: rgba(0,10,18,0.85);
      border: 1px solid rgba(0,255,231,0.35); cursor: pointer; position: relative; transition: border-color 0.15s, box-shadow 0.15s; }
    .map-check-label input[type="checkbox"]:checked { background: rgba(0,255,231,0.15);
      border-color: var(--accent); box-shadow: 0 0 6px rgba(0,255,231,0.5); }
    .map-check-label input[type="checkbox"]:checked::after { content: ''; position: absolute;
      left: 2px; top: 0px; width: 4px; height: 7px;
      border: 1.5px solid var(--accent); border-top: none; border-left: none; transform: rotate(45deg); }
    .map-dz-label { display: flex; align-items: center; gap: 5px;
      font-family: 'Share Tech Mono', monospace; font-size: 9px;
      color: var(--accent); white-space: nowrap; margin-left: 10px; }
    .map-remove-btn { font-family: 'Share Tech Mono', monospace; font-size: 10px;
      padding: 0; width: 26px; height: 24px; background: transparent;
      border: 1px solid rgba(255,60,95,0.3); color: rgba(255,60,95,0.5);
      cursor: pointer; transition: all 0.2s; box-sizing: border-box; }
    .map-remove-btn:hover { border-color: var(--accent2); color: var(--accent2); }
    .map-empty { font-family: 'Share Tech Mono', monospace; font-size: 9px;
      color: var(--dim); text-align: center; padding: 8px 4px; letter-spacing: 1px; }
    /* INPUT MODE TOGGLE */
    .mode-bar { display: flex; align-items: center; justify-content: center; gap: 14px;
      margin-bottom: 14px; }
    .mode-lbl { font-family: 'Share Tech Mono', monospace; font-size: 10px; letter-spacing: 2px;
      color: var(--dim); transition: color 0.2s; user-select: none; text-transform: uppercase; }
    .mode-lbl.active { color: var(--accent); text-shadow: 0 0 8px rgba(0,255,231,0.4); }
    .mode-lbl.dimmed { color: #1a2a30 !important; }
    /* Toggle stays blue in both positions — only the label text colour changes. */
    .toggle-track { position: relative; width: 52px; height: 26px; border-radius: 13px;
      background: rgba(0,20,30,0.8); border: 1px solid var(--accent);
      box-shadow: 0 0 8px rgba(0,255,231,0.25);
      cursor: pointer; transition: all 0.25s; flex-shrink: 0; }
    .toggle-thumb { position: absolute; top: 3px; left: 3px; width: 18px; height: 18px;
      border-radius: 50%; background: var(--accent); transition: transform 0.25s; }
    .toggle-track.joystick .toggle-thumb { transform: translateX(26px); }
    .toggle-track.disabled { opacity: 0.35; cursor: not-allowed; }
    /* CONTROL_FUNCTIONS sub-section panels (JOYSTICK / SLIDERS) — match the main menus */
    .cf-subhead { display: flex; align-items: center; justify-content: space-between;
      padding: 6px 12px; border: 1px solid var(--border); background: rgba(5,10,16,0.80);
      cursor: pointer; font-family: 'Share Tech Mono', monospace; font-size: 10px;
      color: var(--accent); letter-spacing: 2px; user-select: none; backdrop-filter: blur(6px);
      margin-top: 10px; }
    .cf-subhead:hover { color: #fff; }
    .cf-subbody { border: 1px solid var(--border); border-top: none;
      background: rgba(5,10,16,0.72); padding: 12px; backdrop-filter: blur(6px); }
    /* SERVO GRID */
    .servo-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 24px; }
    @media(max-width:560px) { .servo-grid { grid-template-columns: 1fr; } }
    .servo-item { display: flex; align-items: center; gap: 8px; margin-bottom: 8px; }
    .servo-label { min-width: 72px; font-family: 'Share Tech Mono', monospace; font-size: 9px;
      color: var(--dim); letter-spacing: 1px; white-space: nowrap; }
    input[type=range] { flex: 1; accent-color: var(--accent); cursor: pointer; height: 5px; }
    .servo-val { min-width: 30px; text-align: right; font-family: 'Share Tech Mono', monospace;
      font-size: 10px; font-weight: 700; color: var(--accent); }
    .ep-btns { display: flex; gap: 4px; margin: 2px 0 3px 80px; }
    .ep-btn { flex: 1; padding: 3px 0; background: transparent; font-family: 'Share Tech Mono', monospace;
      font-size: 8px; letter-spacing: 0; cursor: pointer; border: 1px solid rgba(0,255,231,0.3);
      color: var(--accent); transition: background .15s, box-shadow .15s; }
    .ep-btn:hover { background: rgba(0,255,231,0.1); border-color: var(--accent); }
    .ep-btn-mid { border-color: rgba(255,214,0,0.35) !important; color: #ffd600 !important; }
    .ep-btn-mid:hover { background: rgba(255,214,0,0.08) !important; border-color: #ffd600 !important; }
    .ep-btn-max { border-color: rgba(255,60,95,0.35) !important; color: var(--accent2) !important; }
    .ep-btn-max:hover { background: rgba(255,60,95,0.08) !important; border-color: var(--accent2) !important; }
    .ep-btn-set { box-shadow: 0 0 6px currentColor; opacity: 1; }
    .ep-readout { display: flex; gap: 10px; font-family: 'Share Tech Mono', monospace;
      font-size: 8px; color: rgba(0,255,231,0.4); margin: 0 0 7px 80px; }
    .ep-readout b { color: rgba(0,255,231,0.85); }
    /* CUSTOM 4-HANDLE SERVO TRACK (µs scale 500–2500) */
    .srv-card { margin-bottom: 11px; }
    .srv-top { display: flex; justify-content: space-between; align-items: baseline; margin-bottom: 3px; }
    .srv-name { font-family: 'Share Tech Mono', monospace; font-size: 12px; color: var(--accent); letter-spacing: 1px; }
    .srv-readout { font-family: 'Share Tech Mono', monospace; font-size: 10px; color: rgba(0,255,231,0.8); }
    .srv-readout b { color: var(--accent); }
    .srv-track { position: relative; height: 24px; margin-top: 8px;
      background: linear-gradient(180deg, rgba(0,30,40,0.7), rgba(0,12,20,0.7));
      border: 1px solid rgba(0,255,231,0.22); touch-action: none; user-select: none;
      box-shadow: inset 0 0 10px rgba(0,255,231,0.05); }
    /* active min→max band — neon gradient with a glowing top edge */
    .srv-fill { position: absolute; top: 0; bottom: 0; pointer-events: none; z-index: 1;
      background: linear-gradient(180deg, rgba(0,255,231,0.16), rgba(0,255,231,0.03));
      border-top: 1px solid rgba(0,255,231,0.45); box-shadow: inset 0 1px 8px rgba(0,255,231,0.12); }
    /* ── handles ─────────────────────────────────────────── */
    .srv-h { position: absolute; top: 0; bottom: 0; width: 18px; transform: translateX(-50%);
      cursor: ew-resize; touch-action: none; z-index: 2; transition: filter .12s; }
    .srv-h:hover { filter: brightness(1.45); }
    .srv-h:active { filter: brightness(1.7); }
    .srv-min { --hc: var(--accent); }
    .srv-mid { --hc: var(--accent); }
    .srv-max { --hc: var(--accent); }
    /* glowing neon stem (min/max) */
    .srv-h::before { content: ''; position: absolute; left: 50%; top: 1px; bottom: 1px; width: 2px;
      transform: translateX(-50%); background: var(--hc);
      box-shadow: 0 0 4px var(--hc), 0 0 9px var(--hc); }
    /* end-stops (min/max): angular flag pointing down into the track */
    .srv-h::after { content: ''; position: absolute; left: 50%; top: -7px; transform: translateX(-50%);
      width: 0; height: 0; border-left: 5px solid transparent; border-right: 5px solid transparent;
      border-top: 7px solid var(--hc); filter: drop-shadow(0 0 3px var(--hc)); }
    /* position thumb — cyan diamond, no glow */
    .srv-pos { position: absolute; top: 50%; width: 16px; height: 16px;
      transform: translate(-50%,-50%) rotate(45deg);
      background: rgba(0,255,231,0.3); border: 2px solid var(--accent);
      box-shadow: none; cursor: grab; touch-action: none; z-index: 3; transition: background .12s; }
    .srv-pos:hover { background: rgba(0,255,231,0.5); }
    .srv-pos:active { cursor: grabbing; }
    /* Joystick mode: handles stay fully visible but aren't mouse-draggable
       (the position thumb still tracks the live gamepad value). */
    body.joymode .srv-pos,
    body.joymode .srv-h { cursor: default; }
    /* RECORDING */
    @keyframes rec-blink { 0%,100%{opacity:1} 50%{opacity:0.15} }
    #rec-indicator { position:absolute; top:8px; right:8px; display:none; align-items:center; gap:6px;
      padding:3px 9px; background:rgba(5,10,14,0.80); border:1px solid rgba(255,60,95,0.45);
      backdrop-filter:blur(4px); z-index:20; font-family:'Share Tech Mono',monospace;
      font-size:10px; color:var(--accent2); letter-spacing:2px; }
    #rec-indicator.active { display:flex; }
    #rec-dot { width:7px; height:7px; border-radius:50%; background:var(--accent2);
      flex-shrink:0; box-shadow:0 0 6px var(--accent2); animation:rec-blink 1s ease-in-out infinite; }
    .ctrl-btn.recording { border-color:var(--accent2)!important; color:var(--accent2)!important;
      animation:rec-blink 1.2s ease-in-out infinite; }
    #rec-btn { min-width: 72px; text-align: center; }
    /* SYSTEM LOG */
    #log-wrap { flex-shrink: 0; position: relative; }
    #log-header { display: flex; justify-content: space-between; align-items: center;
      padding: 6px 12px; border: 1px solid var(--border); background: rgba(5,10,16,0.80);
      cursor: pointer; font-family: 'Share Tech Mono', monospace; font-size: 10px;
      color: var(--accent); letter-spacing: 2px; backdrop-filter: blur(6px); }
    #log-output { max-height: 120px; overflow-y: auto; background: rgba(5,10,16,0.78);
      border: 1px solid var(--border); border-top: none; padding: 6px 10px;
      font-family: 'Share Tech Mono', monospace; font-size: 10px; line-height: 1.6;
      backdrop-filter: blur(6px); }
    .log-entry { color: var(--accent); }
    .log-entry.err { color: var(--accent2); }
    .log-entry.warn { color: var(--dim); }
    /* CAMERA SETTINGS */
    #cam-wrap { flex-shrink: 0; position: relative; }
    #cam-header { display: flex; justify-content: space-between; align-items: center;
      padding: 6px 12px; border: 1px solid var(--border); background: rgba(5,10,16,0.80);
      cursor: pointer; font-family: 'Share Tech Mono', monospace; font-size: 10px;
      color: var(--accent); letter-spacing: 2px; backdrop-filter: blur(6px); }
    #cam-body { border: 1px solid var(--border); border-top: none;
      background: rgba(5,10,16,0.72); padding: 12px; backdrop-filter: blur(6px); display: none; }
    .cam-row { display: flex; align-items: center; gap: 8px; margin-bottom: 9px; flex-wrap: wrap; }
    .cam-lbl { min-width: 90px; font-family: 'Share Tech Mono', monospace; font-size: 9px;
      color: var(--dim); letter-spacing: 1px; flex-shrink: 0; }
    .cam-select { appearance: none; -webkit-appearance: none;
      background: rgba(0,20,30,0.75) url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='8' height='8' viewBox='0 0 8 8'%3E%3Cpath fill='%2300ffe7' d='M0 2l4 4 4-4z'/%3E%3C/svg%3E") no-repeat right 8px center;
      border: 1px solid rgba(0,255,231,0.3); color: var(--accent);
      font-family: 'Share Tech Mono', monospace; font-size: 9px;
      padding: 5px 24px 5px 8px; outline: none; cursor: pointer; letter-spacing: 1px;
      transition: border-color 0.2s; }
    .cam-select:hover { border-color: var(--accent); }
    .cam-select option { background: #050a12; }
    .cam-toggle-btn { font-family: 'Share Tech Mono', monospace; font-size: 9px; letter-spacing: 1px;
      padding: 5px 12px; background: rgba(0,20,30,0.75); border: 1px solid rgba(0,255,231,0.3);
      color: var(--dim); cursor: pointer; transition: all 0.2s; text-transform: uppercase; }
    .cam-toggle-btn.on { border-color: var(--accent); color: var(--accent);
      background: rgba(0,255,231,0.08); box-shadow: 0 0 8px rgba(0,255,231,0.2); }
    .cam-slider-val { min-width: 24px; text-align: right; font-family: 'Share Tech Mono', monospace;
      font-size: 9px; color: var(--accent); }
    /* Two-column settings layout: camera (left) | controller (right) */
    /* Two columns joined as one box with a single vertical divider down the middle */
    .settings-cols { display: grid; grid-template-columns: 1fr 1fr; gap: 0; align-items: stretch;
      border: 1px solid var(--border); background: rgba(5,10,16,0.45); }
    @media(max-width:560px) { .settings-cols { grid-template-columns: 1fr; } }
    .settings-col { min-width: 0; padding: 12px; }
    .settings-col-ctrl { border-left: 1px solid var(--border); }
    @media(max-width:560px) { .settings-col-ctrl { border-left: none; border-top: 1px solid var(--border); } }
    .settings-col-head { font-family: 'Share Tech Mono', monospace; font-size: 10px; letter-spacing: 2px;
      color: var(--accent); text-transform: uppercase; margin: -12px -12px 12px; padding: 10px 12px 6px;
      border-bottom: 1px solid var(--border); }
    /* Live controller graphic */
    #cg-wrap { display: flex; justify-content: center; padding: 2px 0 10px; }
    #cg-svg { width: 200px; max-width: 72%; height: auto; }
    #cg-svg .cg-el { fill: rgba(0,255,231,0.12); stroke: rgba(0,255,231,0.4); stroke-width: 1; }
    #cg-lstick, #cg-rstick, #cg-svg .cg-el, #cg-lt, #cg-rt,
    #cg-a, #cg-b, #cg-x, #cg-y { transition: fill .05s, opacity .05s; }
  </style>
</head>
<body>
<div id="flat-ui">

  <!-- HEADER -->
  <div id="header">
    <div>
      <div class="logo"><span class="logo-32sc">32</span><span class="logo-cam">&nbsp;SERVO CONTROLLER</span></div>
      <div class="logo-subtitle">&#9658;&nbsp;&nbsp;v8.7&nbsp;&nbsp;&#9668;</div>
    </div>
    <!-- dot/status-text kept hidden for JS use -->
    <div style="display:none"><div class="dot" id="dot"></div><span id="status-text"></span></div>
    <button class="ctrl-btn btn-danger" onclick="location.href='/wifi-setup'">&#x21BA; WIFI SETUP</button>
  </div>

  <!-- MAIN SCREEN -->
  <div id="call-screen">

    <!-- VIDEO FEED -->
    <div class="video-wrap">
     <div class="feeds">
      <div id="video-panel">
        <span class="vid-label">LIVE FEED</span>
        <div id="vid-fs" title="Fullscreen" onclick="toggleFullscreen()">&#9974;</div>
        <img id="stream" alt="">
        <div id="calling-spinner">
          <div class="cs-ring"></div>
          <div class="spinner-label">CONNECTING...</div>
        </div>
        <!-- Recording indicator overlay -->
        <div id="rec-indicator"><div id="rec-dot"></div><span id="rec-timer-display">00:00</span></div>
        <div id="vid-resize"></div>
      </div>
      <!-- THERMAL FEED (SPILCD_SDCARD addition) — MLX90640 grid from /thermal -->
      <div id="thermal-panel">
        <span class="vid-label">THERMAL</span>
        <canvas id="thermal-canvas" width="320" height="240"></canvas>
        <div id="thermal-status" class="searching">CONNECTING...</div>
        <div id="thermal-spot"></div>
        <div id="thermal-scale"></div>
        <div id="thermal-read">
          <div class="th-cell"><span class="th-lbl">MAX</span><span class="th-val" id="th-max">--</span></div>
          <div class="th-cell"><span class="th-lbl">CENTRE</span><span class="th-val" id="th-centre">--</span></div>
          <div class="th-cell"><span class="th-lbl">MIN</span><span class="th-val" id="th-min">--</span></div>
          <div class="th-cell"><span class="th-lbl">AMBIENT</span><span class="th-val" id="th-amb">--</span></div>
        </div>
        <div id="thermal-tools">
          <button class="cam-toggle-btn" id="th-mirror" onclick="thermalView('m')">MIRROR</button>
          <button class="cam-toggle-btn" id="th-flip"   onclick="thermalView('f')">FLIP</button>
          <button class="cam-toggle-btn" id="th-rot"    onclick="thermalView('r')">ROT 0&deg;</button>
          <button class="cam-toggle-btn" id="th-enh"    onclick="thermalView('e')">ENHANCED</button>
        </div>
      </div>
     </div>
    </div>

    <!-- HUD BAR -->
    <div id="hud">
      <div class="hud-chip">
        <span class="hud-val ok" id="fps">--</span>
        <span class="hud-unit">FPS</span>
      </div>
      <div class="hud-chip">
        <span class="hud-val" id="kbps">--</span>
        <span class="hud-unit">KB/s</span>
        <div class="tp-wrap"><div class="tp-fill" id="tp-bar"></div></div>
      </div>
      <div class="hud-spacer"></div>
      <button class="ctrl-btn" onclick="snapshot()">&#x1F4F7; SNAP</button>
      <button class="ctrl-btn" id="rec-btn" onclick="toggleRecording()">&#9210; REC</button>
    </div>

    <!-- CONTROL FUNCTIONS -->
    <div id="ctrl-wrap">
      <div id="ctrl-header" onclick="toggleCtrl()">
        <span><span style="color:var(--accent2)">//</span> CONTROL_FUNCTIONS</span>
        <span id="ctrl-toggle">&#9656;</span>
      </div>
      <div id="ctrl-body" style="display:none">
        <!-- Input mode selector — chooses whether sliders or the gamepad drive the servos -->
        <div class="mode-bar">
          <span class="mode-lbl active" id="lbl-slider">Manual Control</span>
          <div class="toggle-track" id="mode-toggle" onclick="toggleInputMode()">
            <div class="toggle-thumb"></div>
          </div>
          <span class="mode-lbl" id="lbl-joystick">Joystick</span>
        </div>

        <div class="cf-subhead" onclick="toggleSub('slid')"><span><span style="color:var(--accent2)">//</span> END AND MID POINT SETTINGS</span><span id="slid-sub-toggle">&#9656;</span></div>
        <div id="slid-sub-body" class="cf-subbody" style="display:none">
        <div class="servo-grid">
          <div id="col-a"></div>
          <div id="col-b"></div>
        </div>
        </div>

        <div class="cf-subhead" onclick="toggleSub('joy')"><span><span style="color:var(--accent2)">//</span> JOYSTICK</span><span id="joy-sub-toggle">&#9656;</span></div>
        <div id="joy-sub-body" class="cf-subbody" style="display:none">
        <div id="gp-status-bar">
          <span id="gp-status">PRESS A BUTTON TO ACTIVATE CONTROLLER</span>
        </div>
        <!-- Live controller graphic — mirrors the physical gamepad (hidden until activated) -->
        <div id="cg-wrap" style="display:none">
          <svg id="cg-svg" viewBox="0 0 220 150" preserveAspectRatio="xMidYMid meet">
            <!-- triggers -->
            <rect id="cg-lt" x="56" y="9"  width="22" height="8" rx="3" fill="#00ffe7" opacity="0.15"/>
            <rect id="cg-rt" x="142" y="9" width="22" height="8" rx="3" fill="#00ffe7" opacity="0.15"/>
            <!-- bumpers -->
            <rect id="cg-lb" x="50" y="20" width="34" height="9" rx="4" class="cg-el"/>
            <rect id="cg-rb" x="136" y="20" width="34" height="9" rx="4" class="cg-el"/>
            <!-- body -->
            <path d="M34,46 Q30,28 56,28 L164,28 Q190,28 186,46 Q198,82 182,116 Q172,134 152,124 Q134,114 126,102 L94,102 Q86,114 68,124 Q48,134 38,116 Q22,82 34,46 Z"
                  fill="rgba(8,16,28,0.92)" stroke="rgba(0,255,231,0.55)" stroke-width="1.5"/>
            <!-- left stick -->
            <circle cx="62" cy="58" r="15" fill="rgba(0,0,0,0.45)" stroke="rgba(0,255,231,0.3)" stroke-width="1"/>
            <circle id="cg-lstick" cx="62" cy="58" r="9" fill="rgba(0,255,231,0.22)" stroke="#00ffe7" stroke-width="1.5"/>
            <!-- right stick -->
            <circle cx="138" cy="92" r="15" fill="rgba(0,0,0,0.45)" stroke="rgba(0,255,231,0.3)" stroke-width="1"/>
            <circle id="cg-rstick" cx="138" cy="92" r="9" fill="rgba(0,255,231,0.22)" stroke="#00ffe7" stroke-width="1.5"/>
            <!-- d-pad -->
            <rect id="cg-dup"    x="64" y="83"  width="12" height="11" rx="2" class="cg-el"/>
            <rect id="cg-ddown"  x="64" y="106" width="12" height="11" rx="2" class="cg-el"/>
            <rect id="cg-dleft"  x="52" y="95"  width="11" height="12" rx="2" class="cg-el"/>
            <rect id="cg-dright" x="77" y="95"  width="11" height="12" rx="2" class="cg-el"/>
            <!-- ABXY (Xbox colours) -->
            <circle id="cg-y" cx="150" cy="44" r="7.5" fill="rgba(0,0,0,0.4)" stroke="#ffd600" stroke-width="1.3"/>
            <circle id="cg-x" cx="135" cy="58" r="7.5" fill="rgba(0,0,0,0.4)" stroke="#00aaff" stroke-width="1.3"/>
            <circle id="cg-b" cx="165" cy="58" r="7.5" fill="rgba(0,0,0,0.4)" stroke="#ff3c5f" stroke-width="1.3"/>
            <circle id="cg-a" cx="150" cy="72" r="7.5" fill="rgba(0,0,0,0.4)" stroke="#39ff14" stroke-width="1.3"/>
            <text x="150" y="46.5" text-anchor="middle" font-size="7" fill="#ffd600" font-family="monospace">Y</text>
            <text x="135" y="60.5" text-anchor="middle" font-size="7" fill="#00aaff" font-family="monospace">X</text>
            <text x="165" y="60.5" text-anchor="middle" font-size="7" fill="#ff3c5f" font-family="monospace">B</text>
            <text x="150" y="74.5" text-anchor="middle" font-size="7" fill="#39ff14" font-family="monospace">A</text>
            <!-- back / start -->
            <circle id="cg-back"  cx="94"  cy="60" r="4" class="cg-el"/>
            <circle id="cg-start" cx="110" cy="60" r="4" class="cg-el"/>
          </svg>
        </div>
        <div class="map-section">
          <div class="map-section-header">
            <span class="map-section-label" style="color:var(--accent)"><span style="color:var(--accent2)">//</span> AXIS &rarr; SERVO</span>
            <button class="map-add-btn" onclick="addAxisMapping()">&#xFF0B; ADD_AXIS</button>
          </div>
          <div id="axis-mappings"></div>
        </div>
        <div class="map-section">
          <div class="map-section-header">
            <span class="map-section-label" style="color:var(--accent)"><span style="color:var(--accent2)">//</span> BUTTON &rarr; SERVO</span>
            <button class="map-add-btn" onclick="addButtonMapping()">&#xFF0B; ADD_BUTTON</button>
          </div>
          <div id="button-mappings"></div>
        </div>
        <div class="map-section">
          <div class="map-section-header">
            <span class="map-section-label" style="color:var(--accent)"><span style="color:var(--accent2)">//</span> KEY &rarr; SERVO</span>
            <button class="map-add-btn" onclick="addKeyMapping()">&#xFF0B; ADD_KEY</button>
          </div>
          <div id="key-mappings"></div>
        </div>
        </div>
      </div>
    </div>

    <!-- CAMERA SETTINGS -->
    <div id="cam-wrap">
      <div id="cam-header" onclick="toggleCam()">
        <span><span style="color:var(--accent2)">//</span> SETTINGS</span>
        <span id="cam-toggle">&#9656;</span>
      </div>
      <div id="cam-body" style="display:none">
        <div class="settings-cols">
        <div class="settings-col settings-col-cam">
        <div class="settings-col-head"><span style="color:var(--accent2)">//</span> CAMERA</div>

        <!-- Detected sensor model -->
        <div class="cam-row">
          <span class="cam-lbl">SENSOR</span>
          <span id="cam-sensor" style="font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--accent);letter-spacing:1px">--</span>
        </div>

        <!-- Resolution -->
        <div class="cam-row">
          <span class="cam-lbl">RESOLUTION</span>
          <select class="cam-select" id="cam-res" onchange="currentRes=this.value;changeRes(this.value)">
            <option value="QXGA">QXGA 2560&times;1920 &#9733;5MP</option>
            <option value="FHD">FHD  1920&times;1080 &#9733;1080p</option>
            <option value="UXGA">UXGA 1600&times;1200</option>
            <option value="SXGA">SXGA 1280&times;1024</option>
            <option value="XGA" selected>XGA  1024&times;768</option>
            <option value="SVGA">SVGA  800&times;600</option>
            <option value="VGA">VGA   640&times;480</option>
            <option value="CIF">CIF   400&times;296</option>
            <option value="QVGA">QVGA  320&times;240</option>
          </select>
        </div>

        <!-- JPEG Quality / framerate trade-off -->
        <div class="cam-row">
          <span class="cam-lbl">QUALITY</span>
          <input type="range" id="cam-quality" min="6" max="40" value="12" step="1" style="flex:1;accent-color:var(--accent2);height:4px"
            oninput="document.getElementById('cam-qual-val').textContent=this.value;camSet('quality',this.value)"
            title="Lower = sharper but larger frames (slower). Higher = more compression, smaller frames (faster / higher FPS).">
          <span class="cam-slider-val" id="cam-qual-val">12</span>
        </div>
        <div style="font-family:'Share Tech Mono',monospace;font-size:8px;letter-spacing:1px;color:rgba(0,255,231,0.4);margin:-4px 0 6px 90px">
          &larr; sharper &nbsp;·&nbsp; faster / higher FPS &rarr;
        </div>

        <!-- Effect -->
        <div class="cam-row">
          <span class="cam-lbl">EFFECT</span>
          <select class="cam-select" id="cam-effect" onchange="camSet('effect',this.value)">
            <option value="0">None</option>
            <option value="1">Negative</option>
            <option value="2">Grayscale</option>
            <option value="3">Reddish</option>
            <option value="4">Greenish</option>
            <option value="5">Blueish</option>
            <option value="6">Sepia</option>
          </select>
        </div>

        <!-- White Balance -->
        <div class="cam-row">
          <span class="cam-lbl">WHITE BAL</span>
          <select class="cam-select" id="cam-awb" onchange="camSet('awb_mode',this.value)">
            <option value="0">Auto</option>
            <option value="1">Sunny</option>
            <option value="2">Cloudy</option>
            <option value="3">Office</option>
            <option value="4">Home</option>
          </select>
        </div>

        <!-- Night Mode -->
        <div class="cam-row">
          <span class="cam-lbl">NIGHT MODE</span>
          <button class="cam-toggle-btn" id="cam-night" onclick="toggleCamNight()">OFF</button>
        </div>

        <!-- Brightness -->
        <div class="cam-row">
          <span class="cam-lbl">BRIGHTNESS</span>
          <input type="range" id="cam-brightness" min="-2" max="2" value="0" step="1" style="flex:1;accent-color:var(--accent);height:4px"
            oninput="document.getElementById('cam-bright-val').textContent=this.value;camSet('brightness',this.value)">
          <span class="cam-slider-val" id="cam-bright-val">0</span>
        </div>

        <!-- Contrast -->
        <div class="cam-row">
          <span class="cam-lbl">CONTRAST</span>
          <input type="range" id="cam-contrast" min="-2" max="2" value="0" step="1" style="flex:1;accent-color:var(--accent);height:4px"
            oninput="document.getElementById('cam-contrast-val').textContent=this.value;camSet('contrast',this.value)">
          <span class="cam-slider-val" id="cam-contrast-val">0</span>
        </div>

        <!-- Saturation -->
        <div class="cam-row">
          <span class="cam-lbl">SATURATION</span>
          <input type="range" id="cam-saturation" min="-2" max="2" value="0" step="1" style="flex:1;accent-color:var(--accent);height:4px"
            oninput="document.getElementById('cam-sat-val').textContent=this.value;camSet('saturation',this.value)">
          <span class="cam-slider-val" id="cam-sat-val">0</span>
        </div>

        <!-- Sharpness -->
        <div class="cam-row">
          <span class="cam-lbl">SHARPNESS</span>
          <input type="range" id="cam-sharpness" min="-3" max="3" value="1" step="1" style="flex:1;accent-color:var(--accent);height:4px"
            oninput="document.getElementById('cam-sharp-val').textContent=this.value;camSet('sharpness',this.value)">
          <span class="cam-slider-val" id="cam-sharp-val">1</span>
        </div>

        <!-- Denoise -->
        <div class="cam-row">
          <span class="cam-lbl">DENOISE</span>
          <input type="range" id="cam-denoise" min="0" max="8" value="1" step="1" style="flex:1;accent-color:var(--accent);height:4px"
            oninput="document.getElementById('cam-denoise-val').textContent=this.value;camSet('denoise',this.value)">
          <span class="cam-slider-val" id="cam-denoise-val">1</span>
        </div>

        <!-- H-Mirror / V-Flip -->
        <div class="cam-row">
          <span class="cam-lbl">MIRROR/FLIP</span>
          <button class="cam-toggle-btn" id="cam-hmirror" onclick="toggleCamMirror()">MIRROR OFF</button>
          <button class="cam-toggle-btn" id="cam-vflip"   onclick="toggleCamFlip()">FLIP OFF</button>
        </div>

        <!-- Rotate feed -->
        <div class="cam-row">
          <span class="cam-lbl">ROTATE</span>
          <select class="cam-select" id="cam-rotate" onchange="setCamRotate(this.value)">
            <option value="0" selected>0&deg;</option>
            <option value="90">90&deg; CW</option>
            <option value="180">180&deg;</option>
            <option value="270">270&deg; CW</option>
          </select>
        </div>
        </div><!-- /camera column -->

        <div class="settings-col settings-col-ctrl">
        <div class="settings-col-head"><span style="color:var(--accent2)">//</span> LCD</div>
        <div class="cam-row">
          <span class="cam-lbl">ROTATE LCD</span>
          <button class="cam-toggle-btn" id="ctrl-lcdflip" onclick="toggleLcdRotate()">180&deg; OFF</button>
        </div>
        </div><!-- /controller column -->
        </div><!-- /settings-cols -->

      </div>
    </div>

    <!-- SYSTEM LOG -->
    <div id="log-wrap">
      <div id="log-header" onclick="toggleLog()">
        <span><span style="color:var(--accent2)">//</span> SYSTEM_LOG</span>
        <span id="log-toggle">&#9656;</span>
      </div>
      <div id="log-output" style="display:none"></div>
    </div>

  </div><!-- /#call-screen -->
</div><!-- /#flat-ui -->
<script>
  const STREAM_URL='http://'+location.hostname+':81/stream';
  const img=document.getElementById('stream'),
        spinner=document.getElementById('calling-spinner'),
        spinLabel=spinner.querySelector('.spinner-label'),
        dot=document.getElementById('dot'),
        fpsEl=document.getElementById('fps'),
        kbpsEl=document.getElementById('kbps'),
        tpBar=document.getElementById('tp-bar'),
        statusEl=document.getElementById('status-text');
  let currentRes='XGA';          // tracks the active camera resolution
  let _autoResApplied=false;     // fires changeRes once after first stream connect
  let _suppressStreamError=false;// set during intentional res change to silence onerror
  let paused=false,retryTimer=null,watchdog=null;

  function zeroHud(){fpsEl.textContent='0';fpsEl.className='hud-val';kbpsEl.textContent='0';tpBar.style.width='0%';}
  const MAX_KBPS=4000;
  function pollStats(){
    if(paused)return;
    fetch('/stats').then(r=>r.json()).then(d=>{
      if(d.fps!==undefined){
        fpsEl.textContent=d.fps;
        fpsEl.className='hud-val '+(d.fps>=15?'ok':d.fps>=8?'warn':'');
        if(d.fps>0)resetWatchdog();
      }
      if(d.kbps!==undefined){
        const kBs=Math.round(d.kbps/8);
        kbpsEl.textContent=kBs>=1000?(kBs/1000).toFixed(1)+'M':kBs;
        const pct=Math.min(100,(d.kbps/MAX_KBPS)*100);
        tpBar.style.width=pct+'%';
        tpBar.style.background=pct>75?'var(--accent)':pct>40?'var(--green)':'var(--dim)';
      }
    }).catch(()=>{});
  }
  setInterval(pollStats,1000);

  // ── Camera syslog polling ──
  let _syslogCursor=0;
  function pollSyslog(){
    fetch('/syslog?since='+_syslogCursor)
      .then(r=>r.json())
      .then(d=>{
        if(d.msgs&&d.msgs.length){
          d.msgs.forEach(m=>log('[CAM] '+m,''));
          _syslogCursor=d.total;
        }
      }).catch(()=>{});
  }
  setInterval(pollSyslog,2000);

  function showSpinner(txt){spinner.classList.remove('hidden');spinLabel.textContent=txt;}
  function hideSpinner(){spinner.classList.add('hidden');}

  // ── Camera presence check ─────────────────────────────────
  let _cameraPresent = true;
  function _disableVideoControls(){
    _cameraPresent = false;
    // Show persistent no-camera message — hide rings, show red text
    spinner.classList.remove('hidden');
    spinner.classList.add('no-cam');
    spinLabel.textContent = 'CAMERA NOT CONNECTED';
    // Grey out and block video-related controls
    var camRes=document.getElementById('cam-res'); if(camRes) camRes.disabled=true;
    document.querySelectorAll('.ctrl-btn').forEach(function(btn){
      if(btn.textContent.indexOf('SNAP')!==-1 || btn.textContent.indexOf('REC')!==-1)
        btn.classList.add('vid-ctrl-disabled');
    });
    log('CAMERA NOT CONNECTED — video disabled','err');
  }

  function resetWatchdog(){
    clearTimeout(watchdog);
    watchdog=setTimeout(()=>{
      if(!paused){
        _suppressStreamError=true;  // prevent onerror from firing a duplicate message
        zeroHud();setStatus('error','Reconnecting…');
        img.style.display='none';showSpinner('RECONNECTING...');
        log('WATCHDOG TIMEOUT — reconnecting...','warn');
        img.src='';
        retryTimer=setTimeout(()=>{_suppressStreamError=false;startStream();},3000);
      }
    },8000);
  }
  let _lastNW=0;
  setInterval(()=>{
    if(paused||!img.src)return;
    const nw=img.naturalWidth;
    if(nw===0){_lastNW=0;}
    else if(nw!==_lastNW){_lastNW=nw;resetWatchdog();}
  },200);

  // The live video now streams over UDP to the app, which a browser can't show.
  // For the config page we poll the same-origin /capture snapshot at ~6 fps so
  // there is still a live preview here. STREAM_PREVIEW_FPS controls the rate.
  const STREAM_PREVIEW_MS=160;
  let _pollTimer=null,_previewConnected=false;
  function startStream(){if(!_cameraPresent)return;img.src='/capture?ts='+Date.now();}
  function setStatus(cls,txt){dot.className='dot '+cls;statusEl.textContent=txt;}

  img.onload=()=>{
    hideSpinner();
    img.style.display='block';
    setStatus('live','Live');resetWatchdog();
    applyCamRotation();   // re-fit rotation now that the frame's natural size is known
    if(!_previewConnected){
      _previewConnected=true;
      log('PREVIEW CONNECTED (snapshots)','ok');
      if(!_autoResApplied){
        _autoResApplied=true;
        if(currentRes!=='VGA'){
          log('AUTO-SWITCH → '+currentRes,'');
          setTimeout(()=>changeRes(currentRes),400);
        }
      }
    }
    if(!paused){clearTimeout(_pollTimer);_pollTimer=setTimeout(startStream,STREAM_PREVIEW_MS);}
  };
  img.onerror=()=>{
    if(paused||_suppressStreamError)return;
    clearTimeout(watchdog);zeroHud();setStatus('error','Reconnecting…');
    img.style.display='none';showSpinner('RECONNECTING...');
    log('PREVIEW ERROR — retrying...','err');
    clearTimeout(_pollTimer);_pollTimer=setTimeout(startStream,1000);
  };

  function snapshot(){
    if(!_cameraPresent){log('No camera — snapshot unavailable','err');return;}
    fetch('/capture').then(r=>{if(!r.ok)throw 0;return r.blob();})
      .then(b=>{const a=document.createElement('a');a.href=URL.createObjectURL(b);
                a.download='snap_'+Date.now()+'.jpg';a.click();log('SNAPSHOT SAVED','ok');})
      .catch(()=>{log('SNAPSHOT FAILED','err');alert('Snapshot failed');});
  }

  function toggleFullscreen(){
    var p=document.getElementById('video-panel');if(!p)return;
    var fsEl=document.fullscreenElement||document.webkitFullscreenElement;
    if(!fsEl){
      (p.requestFullscreen||p.webkitRequestFullscreen||p.msRequestFullscreen||function(){}).call(p);
    } else {
      (document.exitFullscreen||document.webkitExitFullscreen||function(){}).call(document);
    }
  }

  function changeRes(val){
    if(val){ camState.res=val; if(!_loadingCfg) saveConfig(); }
    if(!val||!_cameraPresent)return;
    clearTimeout(watchdog);
    _suppressStreamError=true;
    img.src='';img.style.display='none';
    showSpinner('CHANGING TO '+val+'...');
    log('RESOLUTION → '+val,'');
    const delays={QXGA:8000,FHD:7000,UXGA:5000,SXGA:4500,XGA:3500,SVGA:2500,VGA:2000};
    fetch('/set?res='+val)
      .then(()=>setTimeout(()=>{_suppressStreamError=false;startStream();},delays[val]||1500))
      .catch(()=>{_suppressStreamError=false;alert('Could not change resolution');});
  }
  function forgetWifi(){
    if(!confirm('Clear saved WiFi credentials and restart in setup mode?'))return;
    log('WIFI CREDENTIALS CLEARED — restarting...','warn');
    fetch('/forget').then(()=>alert('Done! Restarting into setup mode.'));
  }

  function toggleCtrl(){
    const body=document.getElementById('ctrl-body'),tog=document.getElementById('ctrl-toggle');
    const open=body.style.display!=='none';
    body.style.display=open?'none':'block';tog.textContent=open?'▸':'▾';
  }
  // Nested JOYSTICK / SLIDERS sub-sections inside CONTROL_FUNCTIONS
  function toggleSub(which){
    const map={joy:['joy-sub-body','joy-sub-toggle'],slid:['slid-sub-body','slid-sub-toggle']};
    const ids=map[which]; if(!ids)return;
    const body=document.getElementById(ids[0]),tog=document.getElementById(ids[1]);
    if(!body)return;
    const open=body.style.display!=='none';
    body.style.display=open?'none':'block';
    if(tog)tog.textContent=open?'▸':'▾';
  }
  function toggleCam(){
    const body=document.getElementById('cam-body'),tog=document.getElementById('cam-toggle');
    const open=body.style.display!=='none';
    body.style.display=open?'none':'block';tog.textContent=open?'▸':'▾';
  }

  // ── Controller settings ───────────────────────────────────
  let _lcdFlip=false;
  function _setLcdFlipBtn(){
    const btn=document.getElementById('ctrl-lcdflip');
    btn.textContent=_lcdFlip?'180° ON':'180° OFF';
    btn.classList.toggle('on',_lcdFlip);
  }
  function toggleLcdRotate(){
    _lcdFlip=!_lcdFlip;
    _setLcdFlipBtn();
    fetch('/set?lcdflip='+(_lcdFlip?1:0)).catch(()=>{});
  }
  // Load saved controller settings on page open
  fetch('/ctrlcfg').then(r=>r.json()).then(d=>{
    _lcdFlip=!!d.lcdflip; _setLcdFlipBtn();
  }).catch(()=>{});

  // ── Camera settings helpers ───────────────────────────────
  let camState={}, _loadingCfg=false, _cfgTimer=null;
  function camSet(param,val){
    camState[param]=val;                 // remember for persistence
    if(!_loadingCfg) saveConfig();
    if(!_cameraPresent)return;
    fetch('/set?'+param+'='+encodeURIComponent(val)).catch(()=>{});
  }
  let _nightOn=false;
  function toggleCamNight(){
    _nightOn=!_nightOn;
    const btn=document.getElementById('cam-night');
    btn.textContent=_nightOn?'ON':'OFF';
    btn.classList.toggle('on',_nightOn);
    camSet('night',_nightOn?1:0);
    log('Night mode '+(_nightOn?'ON':'OFF'),'');
  }
  let _mirrorOn=false;
  function toggleCamMirror(){
    _mirrorOn=!_mirrorOn;
    const btn=document.getElementById('cam-hmirror');
    btn.textContent='MIRROR '+(_mirrorOn?'ON':'OFF');
    btn.classList.toggle('on',_mirrorOn);
    camSet('hmirror',_mirrorOn?1:0);
    applyCamRotation();   // SPILCD_SDCARD addition: firmware ignores /set, so mirror client-side
  }
  let _flipOn=false;
  function toggleCamFlip(){
    _flipOn=!_flipOn;
    const btn=document.getElementById('cam-vflip');
    btn.textContent='FLIP '+(_flipOn?'ON':'OFF');
    btn.classList.toggle('on',_flipOn);
    camSet('vflip',_flipOn?1:0);
    applyCamRotation();   // SPILCD_SDCARD addition: firmware ignores /set, so flip client-side
  }
  // ── Camera-feed rotation (client-side CSS transform) ──────────
  let _camRotate=0;
  function setCamRotate(val){
    _camRotate=parseInt(val,10)||0;
    camState.rotate=_camRotate;            // remember for persistence
    if(!_loadingCfg) saveConfig();
    applyCamRotation();
  }
  function applyCamRotation(){
    var img=document.getElementById('stream');
    var panel=document.getElementById('video-panel');
    if(!img||!panel)return;
    var deg=_camRotate;
    // SPILCD_SDCARD addition: mirror/flip as a CSS scale, applied before the
    // rotation (CSS applies right to left) — the same order the THERMAL
    // panel's ENHANCED view uses, so the two always match.
    var sc=(_mirrorOn||_flipOn)?(' scale('+(_mirrorOn?-1:1)+','+(_flipOn?-1:1)+')'):'';
    img.style.transformOrigin='center center';
    if(deg===90||deg===270){
      // Rotate 90/270: size the rotated frame so it FILLS the panel width (no side
      // bars), grow the panel height to match, and absolute-center it.
      var w=panel.clientWidth;
      var ar=(img.naturalWidth&&img.naturalHeight)?(img.naturalHeight/img.naturalWidth):0.75;
      img.style.position='absolute'; img.style.left='50%'; img.style.top='50%';
      img.style.width='auto'; img.style.height=w+'px';   // rotated width = w = full panel width
      img.style.transform='translate(-50%,-50%) rotate('+deg+'deg)'+sc;
      panel.style.height=(w/ar)+'px';
    } else {
      // 0/180: clear inline overrides so the stylesheet (and fullscreen object-fit) governs.
      img.style.position=''; img.style.left=''; img.style.top='';
      img.style.width=''; img.style.height='';
      panel.style.height='';
      img.style.transform=(deg?('rotate('+deg+'deg)'):'')+sc;
    }
  }
  window.addEventListener('resize',applyCamRotation);

  // ── Video panel drag-resize handle
  document.addEventListener('DOMContentLoaded', function() {
    var panel  = document.getElementById('video-panel');
    var handle = document.getElementById('vid-resize');
    if (!panel || !handle) return;
    var wrap = panel.closest('.video-wrap') || panel.parentElement;
    var dragging = false, startX, startY, startW, startH;
    handle.addEventListener('pointerdown', function(e) {
      e.preventDefault();
      dragging = true;
      startX = e.clientX; startY = e.clientY;
      startW = panel.offsetWidth;
      startH = panel.offsetHeight;
      panel.style.width  = startW + 'px';
      panel.style.height = startH + 'px';
      document.body.style.userSelect = 'none';
      handle.setPointerCapture(e.pointerId);
    });
    handle.addEventListener('pointermove', function(e) {
      if (!dragging) return;
      e.preventDefault();
      var dx = e.clientX - startX;
      var dy = e.clientY - startY;
      var maxW = wrap.offsetWidth;
      // Side by side with the thermal panel: stop at it rather than run under it.
      var tp = document.getElementById('thermal-panel');
      if (tp && tp.offsetLeft > panel.offsetLeft) maxW -= tp.offsetWidth + 10;
      panel.style.width  = Math.min(maxW, Math.max(160, startW + dx * 2)) + 'px';
      if (_camRotate === 90 || _camRotate === 270) {
        applyCamRotation();   // rotated: height derives from width, re-fit to kill side bars
      } else {
        panel.style.height = Math.max(90, startH + dy) + 'px';
      }
    });
    handle.addEventListener('pointerup',     function() { dragging = false; document.body.style.userSelect = ''; });
    handle.addEventListener('pointercancel', function() { dragging = false; document.body.style.userSelect = ''; });
  });

  // Check camera presence first, then start stream or show no-camera message
  fetch('/camstatus').then(function(r){return r.json();}).then(function(d){
    var sl=document.getElementById('cam-sensor');
    if(sl)sl.textContent=(d.available?(d.sensor||'CAMERA'):'NO CAM');
    if(!d.available){
      _disableVideoControls();
    } else {
      // The firmware cold-boots the camera at the saved resolution and reports it,
      // so just sync the UI to the actual resolution and stream — no reinit needed.
      if(d.res){
        currentRes=d.res;
        var rd=document.getElementById('cam-res'); if(rd)rd.value=d.res;
      }
      _autoResApplied=true;
      spinLabel.textContent='CONNECTING...';
      startStream();
    }
  }).catch(function(){
    // If endpoint unreachable just try to connect normally
    spinLabel.textContent='CONNECTING...';
    startStream();
  });

  let inputMode='slider',gamepadConnected=false;
  function setToggleEnabled(enabled){
    const track=document.getElementById('mode-toggle'),lblJoy=document.getElementById('lbl-joystick');
    if(enabled){track.classList.remove('disabled');lblJoy.classList.remove('dimmed');}
    else{track.classList.add('disabled');lblJoy.classList.add('dimmed');}
  }
  function toggleInputMode(){
    if(!gamepadConnected)return;
    inputMode=(inputMode==='slider')?'joystick':'slider';
    const track=document.getElementById('mode-toggle'),
          lblSlider=document.getElementById('lbl-slider'),
          lblJoy=document.getElementById('lbl-joystick');
    if(inputMode==='joystick'){track.classList.add('joystick');lblSlider.classList.remove('active');lblJoy.classList.add('active');}
    else{track.classList.remove('joystick');lblJoy.classList.remove('active');lblSlider.classList.add('active');}
    document.body.classList.toggle('joymode', inputMode==='joystick');
    if(!_loadingCfg) saveConfig();
  }
  function forceSliderMode(){
    if(inputMode==='joystick'){
      inputMode='slider';
      const track=document.getElementById('mode-toggle'),
            lblSlider=document.getElementById('lbl-slider'),
            lblJoy=document.getElementById('lbl-joystick');
      track.classList.remove('joystick');lblJoy.classList.remove('active');lblSlider.classList.add('active');
    }
    document.body.classList.remove('joymode');
  }

  const sliders=[],lastSent=new Array(32).fill(0);
  var epData={};
  const EP_DEF={min:600,mid:1500,max:2400,boot:127};
  const US_MIN=500, US_MAX=2500, US_SPAN=US_MAX-US_MIN;

  function _ep(ch){ if(!epData[ch])epData[ch]={min:EP_DEF.min,mid:EP_DEF.mid,max:EP_DEF.max,boot:EP_DEF.boot};
    if(epData[ch].boot===undefined)epData[ch].boot=EP_DEF.boot; return epData[ch]; }
  function usToPct(u){ return ((u-US_MIN)/US_SPAN)*100; }
  function clampU(u){ return Math.max(US_MIN,Math.min(US_MAX,Math.round(u))); }
  // Replicates firmware applyEndpoints(): 0–255 input value → output microseconds.
  function valToUs(v,ch){ const d=_ep(ch); let us;
    if(v<=127) us=d.min+(d.mid-d.min)*v/127; else us=d.mid+(d.max-d.mid)*(v-127)/128;
    return Math.max(US_MIN,Math.min(US_MAX,us)); }
  // Inverse: a target output µs (clamped to min..max) → nearest 0–255 input value.
  function usToVal(u,ch){ const d=_ep(ch); u=Math.max(d.min,Math.min(d.max,u)); let v;
    if(u<=d.mid){ const den=(d.mid-d.min)||1; v=(u-d.min)*127/den; }
    else { const den=(d.max-d.mid)||1; v=127+(u-d.mid)*128/den; }
    return Math.max(0,Math.min(255,Math.round(v))); }

  function buildSliders(){
    const colA=document.getElementById('col-a'),colB=document.getElementById('col-b');
    for(let i=0;i<32;i++){
      // Hidden range input — keeps the gamepad/key-mapping + poll code working unchanged.
      const sl=document.createElement('input'); sl.type='range'; sl.min=0; sl.max=255; sl.value=0;
      sl.id='sl'+i; sl.style.display='none'; sliders.push(sl);
      const card=document.createElement('div'); card.className='srv-card';
      const top=document.createElement('div'); top.className='srv-top';
      const nm=document.createElement('span'); nm.className='srv-name'; nm.textContent='SERVO '+(i+1);
      const ro=document.createElement('span'); ro.className='srv-readout'; ro.id='sro'+i;
      // Captures wherever the position thumb currently sits as this channel's
      // power-up value — the pulse the ESC/servo sees before any host connects.
      const bb=document.createElement('button'); bb.textContent='SET BOOT'; bb.id='sbtn'+i;
      bb.title='Store the current position as this channel\'s power-up pulse';
      bb.style.cssText='padding:0 6px;height:16px;font-size:7px;letter-spacing:0;margin-left:6px;'
                      +'border:1px solid rgba(0,255,231,.35);background:transparent;color:var(--accent);cursor:pointer';
      bb.addEventListener('pointerdown',function(e){e.stopPropagation();});
      bb.addEventListener('click',function(e){
        e.preventDefault(); e.stopPropagation();
        _ep(i).boot=parseInt(sliders[i].value)||0;
        postEndpoint(i); renderServoTrack(i);
      });
      top.appendChild(nm); top.appendChild(ro); top.appendChild(bb);
      // Hidden value element so setSlider's getElementById('v'+i) keeps working.
      const vd=document.createElement('span'); vd.id='v'+i; vd.style.display='none'; vd.textContent='0';
      const track=document.createElement('div'); track.className='srv-track'; track.id='strk'+i;
      const fill=document.createElement('div'); fill.className='srv-fill'; fill.id='sfill'+i;
      const hmin=document.createElement('div'); hmin.className='srv-h srv-min'; hmin.id='smin'+i;
      const hmid=document.createElement('div'); hmid.className='srv-h srv-mid'; hmid.id='smid'+i;
      const hmax=document.createElement('div'); hmax.className='srv-h srv-max'; hmax.id='smax'+i;
      const pos =document.createElement('div'); pos.className='srv-pos'; pos.id='spos'+i;
      track.appendChild(fill);track.appendChild(hmin);track.appendChild(hmid);track.appendChild(hmax);track.appendChild(pos);
      card.appendChild(top);card.appendChild(vd);card.appendChild(sl);card.appendChild(track);
      (i<16?colA:colB).appendChild(card);
      _wireServoTrack(i, track, {min:hmin,mid:hmid,max:hmax,pos:pos});
    }
    for(let i=0;i<32;i++) renderServoTrack(i);
  }

  function renderServoTrack(i){
    const d=_ep(i);
    const mn=document.getElementById('smin'+i); if(!mn)return;
    document.getElementById('smin'+i).style.left=usToPct(d.min)+'%';
    document.getElementById('smid'+i).style.left=usToPct(d.mid)+'%';
    document.getElementById('smax'+i).style.left=usToPct(d.max)+'%';
    const fl=document.getElementById('sfill'+i);
    fl.style.left=usToPct(d.min)+'%'; fl.style.width=(usToPct(d.max)-usToPct(d.min))+'%';
    const v=parseInt(sliders[i].value)||0, u=valToUs(v,i);
    document.getElementById('spos'+i).style.left=usToPct(u)+'%';
    const ro=document.getElementById('sro'+i);
    if(ro)ro.innerHTML='<b>'+v+'</b> · '+Math.round(u)+'µs &nbsp;<span style="color:rgba(0,255,231,.4)">['+d.min+'/'+d.mid+'/'+d.max+']</span>'
      +' <span style="color:rgba(0,255,231,.4)">BOOT '+d.boot+' ('+Math.round(valToUs(d.boot,i))+'µs)</span>';
  }

  let _epPostTimers={};
  function postEndpoint(ch){
    clearTimeout(_epPostTimers[ch]);
    _epPostTimers[ch]=setTimeout(function(){
      const d=_ep(ch);
      fetch('/endpoint',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},
        body:'num='+ch+'&min='+d.min+'&mid='+d.mid+'&max='+d.max+'&boot='+d.boot});
    },120);
  }

  function _wireServoTrack(i, track, h){
    let drag=null;
    function uFromEvent(e){ const r=track.getBoundingClientRect();
      let p=(e.clientX-r.left)/r.width; p=Math.max(0,Math.min(1,p)); return US_MIN+p*US_SPAN; }
    function onMove(e){
      if(!drag)return; const u=uFromEvent(e), d=_ep(i);
      if(drag==='min'){ d.min=clampU(Math.min(u,d.mid)); postEndpoint(i); }
      else if(drag==='max'){ d.max=clampU(Math.max(u,d.mid)); postEndpoint(i); }
      else if(drag==='mid'){ d.mid=clampU(Math.max(d.min,Math.min(u,d.max))); postEndpoint(i); }
      else if(drag==='pos'){ setSlider(i, usToVal(u,i)); }
      renderServoTrack(i);
    }
    function onUp(){ drag=null;
      window.removeEventListener('pointermove',onMove); window.removeEventListener('pointerup',onUp); }
    // In joystick mode all handles (endpoints + position) are mouse-locked.
    function begin(which,e){ if(inputMode==='joystick')return; e.preventDefault(); e.stopPropagation(); drag=which;
      window.addEventListener('pointermove',onMove); window.addEventListener('pointerup',onUp); }
    h.min.addEventListener('pointerdown',function(e){begin('min',e);});
    h.mid.addEventListener('pointerdown',function(e){begin('mid',e);});
    h.max.addEventListener('pointerdown',function(e){begin('max',e);});
    h.pos.addEventListener('pointerdown',function(e){begin('pos',e);});
    // Click on empty track jumps the position thumb there and starts dragging it
    // (also disabled in joystick mode).
    track.addEventListener('pointerdown',function(e){
      if(e.target!==track && e.target.id!==('sfill'+i))return;
      if(inputMode==='joystick')return;
      setSlider(i, usToVal(uFromEvent(e),i)); renderServoTrack(i); begin('pos',e);
    });
  }

  fetch('/endpoints').then(function(r){return r.json();}).then(function(data){
    data.forEach(function(ep){ epData[ep.ch]={min:ep.min,mid:ep.mid,max:ep.max,
      boot:(ep.boot===undefined?EP_DEF.boot:ep.boot)};
      // Channel physically sits at its boot value until a host commands it —
      // seed the slider (and lastSent, so nothing is echoed back) to match, or
      // the UI reads 0 while the hardware holds 127 and the first touch jumps.
      const b=epData[ep.ch].boot;
      if(sliders[ep.ch]){ sliders[ep.ch].value=b; lastSent[ep.ch]=b;
        const vd=document.getElementById('v'+ep.ch); if(vd)vd.textContent=b; }
      renderServoTrack(ep.ch); });
  }).catch(function(){});
  function sendServo(num,val){fetch('/servo?num='+num+'&val='+val);}
  setInterval(function(){
    sliders.forEach(function(sl,i){
      const val=parseInt(sl.value);
      if(val!==lastSent[i]){lastSent[i]=val;sendServo(i,val);}
    });
  },50);
  buildSliders();

  document.addEventListener('keydown',function(e){
    // ── Key capture mode: assign key to a mapping ──
    if(_capturingKeyFor!==null){
      e.preventDefault();
      if(e.code==='Escape'){_capturingKeyFor=null;renderKeyMappings();return;}
      updKey(_capturingKeyFor,'key',e.code);
      _capturingKeyFor=null;
      renderKeyMappings();
      return;
    }
    // ── Legacy: arrow keys nudge slider 0 in slider mode ──
    if(inputMode==='slider'&&(e.key==='ArrowLeft'||e.key==='ArrowRight')){
      const sl=sliders[0],step=e.shiftKey?10:1;
      let val=parseInt(sl.value);
      if(e.key==='ArrowRight')val=Math.min(255,val+step);
      if(e.key==='ArrowLeft')val=Math.max(0,val-step);
      sl.value=val;document.getElementById('v0').textContent=val;
    }
    // ── Key mappings: rising-edge actions (fires once on first keydown) ──
    if(!keysHeld.has(e.code)){
      keysHeld.add(e.code);
      keyMappings.forEach(function(m){
        if(!m.key||m.key!==e.code)return;
        const srv=m.servo,cur=parseInt(sliders[srv].value);
        if(m.action==='set')    setSlider(srv,m.value);
        if(m.action==='center') setSlider(srv,127);
        if(m.action==='min')    setSlider(srv,0);
        if(m.action==='max')    setSlider(srv,255);
        if(m.action==='toggle'){const k='kt'+m._id;keyToggleState[k]=!keyToggleState[k];setSlider(srv,keyToggleState[k]?255:0);}
      });
    }
  });
  document.addEventListener('keyup',function(e){
    keysHeld.delete(e.code);
  });

  const gpStatus=document.getElementById('gp-status'),gpBadge=document.getElementById('gp-live-badge');
  const AXIS_SOURCES=[
    {id:'LX',label:'Left Stick X',axisIdx:0,isTrigger:false},
    {id:'LY',label:'Left Stick Y',axisIdx:1,isTrigger:false},
    {id:'RX',label:'Right Stick X',axisIdx:2,isTrigger:false},
    {id:'RY',label:'Right Stick Y',axisIdx:3,isTrigger:false},
    {id:'LT',label:'Left Trigger',axisIdx:4,isTrigger:true},
    {id:'RT',label:'Right Trigger',axisIdx:5,isTrigger:true},
  ];
  const BUTTON_SOURCES=[
    {id:'A',label:'A',btnIdx:0},{id:'B',label:'B',btnIdx:1},
    {id:'X',label:'X',btnIdx:2},{id:'Y',label:'Y',btnIdx:3},
    {id:'LB',label:'LB',btnIdx:4},{id:'RB',label:'RB',btnIdx:5},
    {id:'Back',label:'Back/Select',btnIdx:8},{id:'Start',label:'Start',btnIdx:9},
    {id:'L3',label:'L3 (L-Click)',btnIdx:10},{id:'R3',label:'R3 (R-Click)',btnIdx:11},
    {id:'DUp',label:'D-Pad Up',btnIdx:12},{id:'DDown',label:'D-Pad Down',btnIdx:13},
    {id:'DLeft',label:'D-Pad Left',btnIdx:14},{id:'DRight',label:'D-Pad Right',btnIdx:15},
  ];
  const BTN_ACTIONS=[
    {id:'set',label:'Set Value',hasVal:true},{id:'inc',label:'Increment (hold)',hasVal:true},
    {id:'dec',label:'Decrement (hold)',hasVal:true},{id:'center',label:'Center (127)',hasVal:false},
    {id:'min',label:'Minimum (0)',hasVal:false},{id:'max',label:'Maximum (255)',hasVal:false},
    {id:'toggle',label:'Toggle Min/Max',hasVal:false},
  ];
  let axisMappings=[],buttonMappings=[],keyMappings=[],nextAxisId=0,nextBtnId=0,nextKeyId=0;
  const btnToggleState={},btnPrevState={},keyToggleState={};
  const keysHeld=new Set();  // currently held key codes
  let _capturingKeyFor=null; // mapping _id awaiting a key press, or null

  function servoOpts(sel){let o='';for(let i=0;i<32;i++)o+='<option value="'+i+'"'+(i===sel?' selected':'')+'>SERVO '+(i+1)+'</option>';return o;}
  function axisOpts(sel){return AXIS_SOURCES.map(a=>'<option value="'+a.id+'"'+(a.id===sel?' selected':'')+'>'+a.label+'</option>').join('');}
  function btnOpts(sel){return BUTTON_SOURCES.map(b=>'<option value="'+b.id+'"'+(b.id===sel?' selected':'')+'>'+b.label+'</option>').join('');}
  function actOpts(sel){return BTN_ACTIONS.map(a=>'<option value="'+a.id+'"'+(a.id===sel?' selected':'')+'>'+a.label+'</option>').join('');}

  function makeStepper(cls,val,min,max,step,onch){
    const id='sp'+Math.random().toString(36).slice(2);
    return`<div class="custom-stepper ${cls}">
      <input class="stepper-input" id="${id}" type="text" value="${val}" onchange="${onch.replace('__VAL__','parseFloat(this.value)||0')}">
      <div class="stepper-btns">
        <button class="stepper-btn" onclick="stepperAdj('${id}',${step},${max});${onch.replace('__VAL__','parseFloat(document.getElementById(\''+id+'\').value)||0')}">&#9650;</button>
        <button class="stepper-btn" onclick="stepperAdj('${id}',-${step},${max});${onch.replace('__VAL__','parseFloat(document.getElementById(\''+id+'\').value)||0')}">&#9660;</button>
      </div></div>`;
  }
  function stepperAdj(id,delta,max){
    const el=document.getElementById(id);
    let v=parseFloat(el.value)||0;
    v=Math.max(0,Math.min(max,+(v+delta).toFixed(2)));
    el.value=v;
  }

  function renderAxisMappings(){
    const c=document.getElementById('axis-mappings');
    if(!axisMappings.length){c.innerHTML='<div class="map-empty">&mdash; NO AXIS MAPPINGS &mdash;</div>';return;}
    c.innerHTML=axisMappings.map(m=>`
      <div class="mapping-row axis-row">
        <select class="map-select" onchange="updAx(${m._id},'axisId',this.value)">${axisOpts(m.axisId)}</select>
        <select class="map-select" onchange="updAx(${m._id},'servo',parseInt(this.value))">${servoOpts(m.servo)}</select>
        <label class="map-check-label"><input type="checkbox" ${m.invert?'checked':''} onchange="updAx(${m._id},'invert',this.checked)"> INV</label>
        <div class="map-dz-label">DZ ${makeStepper('dz-stepper',m.deadzone,0,0.5,0.01,"updAx("+m._id+",'deadzone',__VAL__)")}</div>
        <button class="map-remove-btn" onclick="rmAx(${m._id})">&times;</button>
      </div>`).join('');
  }
  function renderButtonMappings(){
    const c=document.getElementById('button-mappings');
    if(!buttonMappings.length){c.innerHTML='<div class="map-empty">&mdash; NO BUTTON MAPPINGS &mdash;</div>';return;}
    c.innerHTML=buttonMappings.map(m=>{
      const ad=BTN_ACTIONS.find(a=>a.id===m.action)||BTN_ACTIONS[0];
      return`<div class="mapping-row button-row ${ad.hasVal?'has-val':''}">
        <select class="map-select" onchange="updBt(${m._id},'btnId',this.value)">${btnOpts(m.btnId)}</select>
        <select class="map-select" onchange="updBt(${m._id},'servo',parseInt(this.value))">${servoOpts(m.servo)}</select>
        <select class="map-select" onchange="updBt(${m._id},'action',this.value);renderButtonMappings()">${actOpts(m.action)}</select>
        ${ad.hasVal?makeStepper('map-val-stepper',m.value,0,255,1,"updBt("+m._id+",'value',parseInt(__VAL__))"):''}
        <button class="map-remove-btn" onclick="rmBt(${m._id})">&times;</button>
      </div>`;
    }).join('');
  }
  function addAxisMapping(){axisMappings.push({_id:nextAxisId++,axisId:'LX',servo:0,invert:false,deadzone:0.08});renderAxisMappings();saveConfig();}
  function rmAx(id){axisMappings=axisMappings.filter(m=>m._id!==id);renderAxisMappings();saveConfig();}
  function updAx(id,k,v){const m=axisMappings.find(m=>m._id===id);if(m)m[k]=v;saveConfig();}
  function addButtonMapping(){buttonMappings.push({_id:nextBtnId++,btnId:'A',servo:0,action:'set',value:255});renderButtonMappings();saveConfig();}
  function rmBt(id){buttonMappings=buttonMappings.filter(m=>m._id!==id);renderButtonMappings();saveConfig();}
  function updBt(id,k,v){const m=buttonMappings.find(m=>m._id===id);if(m)m[k]=v;saveConfig();}

  // ── KEY → SERVO mappings ──────────────────────────────────────
  function prettyKey(code){
    if(!code)return '— PRESS KEY —';
    return code
      .replace('Arrow','').replace('Key','').replace('Digit','')
      .replace('Numpad','NUM').replace('ShiftLeft','LSHIFT').replace('ShiftRight','RSHIFT')
      .replace('ControlLeft','LCTRL').replace('ControlRight','RCTRL')
      .replace('AltLeft','LALT').replace('AltRight','RALT')
      .replace('Space','SPC').replace('Enter','↵').replace('Backspace','⌫')
      .replace('Tab','TAB').replace('Escape','ESC')
      .replace('Left','←').replace('Right','→').replace('Up','↑').replace('Down','↓')
      .toUpperCase();
  }
  function renderKeyMappings(){
    const c=document.getElementById('key-mappings');
    if(!keyMappings.length){c.innerHTML='<div class="map-empty">&mdash; NO KEY MAPPINGS &mdash;</div>';return;}
    c.innerHTML=keyMappings.map(m=>{
      const ad=BTN_ACTIONS.find(a=>a.id===m.action)||BTN_ACTIONS[0];
      const isCap=_capturingKeyFor===m._id;
      return`<div class="mapping-row key-row ${ad.hasVal?'has-val':''}">
        <button class="key-cap-btn${isCap?' capturing':''}" onclick="startKeyCapture(${m._id})">${isCap?'PRESS KEY…':prettyKey(m.key)}</button>
        <select class="map-select" onchange="updKey(${m._id},'servo',parseInt(this.value))">${servoOpts(m.servo)}</select>
        <select class="map-select" onchange="updKey(${m._id},'action',this.value);renderKeyMappings()">${actOpts(m.action)}</select>
        ${ad.hasVal?makeStepper('map-val-stepper',m.value,0,255,1,"updKey("+m._id+",'value',parseInt(__VAL__))"):''}
        <button class="map-remove-btn" onclick="rmKey(${m._id})">&times;</button>
      </div>`;
    }).join('');
  }
  function addKeyMapping(){keyMappings.push({_id:nextKeyId++,key:'',servo:0,action:'set',value:255});renderKeyMappings();saveConfig();}
  function rmKey(id){keyMappings=keyMappings.filter(m=>m._id!==id);if(_capturingKeyFor===id)_capturingKeyFor=null;renderKeyMappings();saveConfig();}
  function updKey(id,k,v){const m=keyMappings.find(m=>m._id===id);if(m)m[k]=v;saveConfig();}
  function startKeyCapture(id){_capturingKeyFor=id;renderKeyMappings();}

  // Merge a left/right controller pair (Quest, Pico, etc.) into one Xbox-standard
  // gamepad object so all existing axis/button mappings work unchanged.
  // Quest Touch in flat-mode browser report thumbstick at axes[2]/[3] (xr layout),
  // buttons: [0]trigger [1]grip [3]stick-click [4]A/X [5]B/Y.
  function _mergeControllerPair(a,b){
    const left=/right/i.test(a.id)?b:a, right=/right/i.test(a.id)?a:b;
    function stick(p){if(!p)return[0,0];const x=p.axes;return x.length>3?[x[2]||0,x[3]||0]:[x[0]||0,x[1]||0];}
    function btn(o,v){const pr=!!(o&&o.pressed);return{pressed:pr,touched:pr,value:v!==undefined?v:(o?(o.value||(pr?1:0)):0)};}
    const lb=left.buttons||[], rb=right.buttons||[];
    const ls=stick(left), rs=stick(right);
    return{ id:left.id+' + '+right.id, connected:true,
      axes:[ls[0],ls[1],rs[0],rs[1]],
      buttons:[ btn(rb[4]),btn(rb[5]),btn(lb[4]),btn(lb[5]),
                btn(lb[1],lb[1]&&lb[1].value),btn(rb[1],rb[1]&&rb[1].value),
                btn(lb[0],lb[0]&&lb[0].value),btn(rb[0],rb[0]&&rb[0].value),
                btn(lb[2]),btn(rb[2]),btn(lb[3]),btn(rb[3]),
                btn(null),btn(null),btn(null),btn(null) ] };
  }
  function getXboxGamepad(){
    const pads=navigator.getGamepads?Array.from(navigator.getGamepads()):[];
    const c=pads.filter(Boolean);
    if(!c.length)return null;
    // 1. explicit Xbox  2. any standard-mapped pad  3. two pads = VR controller pair  4. single
    const xbox=c.find(p=>p.id.toLowerCase().includes('xbox')); if(xbox)return xbox;
    const std=c.find(p=>p.mapping==='standard'); if(std)return std;
    if(c.length>=2)return _mergeControllerPair(c[0],c[1]);
    return c[0];
  }
  function getAxisValue(gp,axisId){
    const src=AXIS_SOURCES.find(a=>a.id===axisId);if(!src)return 0;
    if(src.isTrigger){const bi=(axisId==='LT')?6:7;return gp.buttons[bi]?gp.buttons[bi].value:0;}
    return gp.axes[src.axisIdx]||0;
  }
  function axisToServo255(rawVal,isTrigger,invert,deadzone){
    let v=rawVal;
    if(!isTrigger){if(Math.abs(v)<deadzone)v=0;v=(v+1)/2;}
    else{if(v<deadzone)v=0;}
    if(invert)v=1-v;
    return Math.round(v*255);
  }
  function setSlider(idx,val){
    val=Math.max(0,Math.min(255,val));sliders[idx].value=val;document.getElementById('v'+idx).textContent=val;
    if(typeof renderServoTrack==='function') renderServoTrack(idx);  // move the visual thumb
  }
  window.addEventListener('gamepadconnected',function(e){
    gamepadConnected=true;
    const np=(navigator.getGamepads?Array.from(navigator.getGamepads()):[]).filter(Boolean).length;
    gpStatus.textContent=np>=2?('VR CONTROLLERS ('+np+' connected)'):e.gamepad.id;
    gpStatus.style.color='var(--accent)';
    if(gpBadge)gpBadge.style.display='inline-block';setToggleEnabled(true);
    // Only show the Xbox graphic for an actual Xbox controller (id text or MS vendor 045e).
    var _cgw=document.getElementById('cg-wrap');
    if(_cgw){var _id=(e.gamepad.id||'').toLowerCase();var _xb=/xbox|xinput|045e/.test(_id);_cgw.style.display=_xb?'flex':'none';}
    log('GAMEPAD CONNECTED: '+e.gamepad.id,'ok');
  });
  window.addEventListener('gamepaddisconnected',function(){
    gamepadConnected=false;gpStatus.textContent='PRESS A BUTTON TO ACTIVATE CONTROLLER';
    gpStatus.style.color='var(--dim)';if(gpBadge)gpBadge.style.display='none';
    var _cgw=document.getElementById('cg-wrap');if(_cgw)_cgw.style.display='none';
    setToggleEnabled(false);forceSliderMode();
    log('GAMEPAD DISCONNECTED','warn');
  });
  setToggleEnabled(false);renderAxisMappings();renderButtonMappings();renderKeyMappings();

  // ── VIDEO RECORDING
  // Uses /capture (port 80, same-origin) polled at ~8 fps rather than drawing
  // the MJPEG stream img directly.  The MJPEG stream is on port 81 — a different
  // origin — so drawing it to a canvas taints the canvas and captureStream()
  // throws a SecurityError.  /capture is always same-origin, zero CORS issues.
  let _recCanvas=null,_recCtx=null,_recMR=null,_recChunks=[];
  let _recStartTime=0,_recTimerInt=null,_recMime='';
  let _recFetchTimer=null,_recBusy=false,_recActive=false;
  const REC_INTERVAL_MS=125;  // ~8 fps — light enough for ESP32 at XGA

  function _recChooseMime(){
    const c=['video/mp4;codecs=avc1','video/mp4','video/webm;codecs=vp9','video/webm;codecs=vp8','video/webm'];
    for(const t of c){if(MediaRecorder.isTypeSupported(t))return t;}return'';
  }
  function _recFmt(ms){const s=Math.floor(ms/1000),m=Math.floor(s/60);return String(m).padStart(2,'0')+':'+String(s%60).padStart(2,'0');}

  function _recLogErr(msg){
    // Open the log panel so the error is immediately visible
    const out=document.getElementById('log-output'),tog=document.getElementById('log-toggle');
    if(out&&out.style.display==='none'){out.style.display='block';if(tog)tog.textContent='▾';}
    log(msg,'err');
  }

  function toggleRecording(){
    if(_recActive)_stopRec();else _startRec();
  }

  function _startRec(){
    _recMime=_recChooseMime();
    if(!_recMime){_recLogErr('MediaRecorder not supported in this browser');return;}

    if(!_recCanvas){
      _recCanvas=document.createElement('canvas');
      _recCanvas.width=1024;_recCanvas.height=768;
      Object.assign(_recCanvas.style,{position:'fixed',left:'-9999px',top:'-9999px',
        width:'1px',height:'1px',opacity:'0',pointerEvents:'none'});
      document.body.appendChild(_recCanvas);
      _recCtx=_recCanvas.getContext('2d');
    }

    let stream;
    try{stream=_recCanvas.captureStream(8);}
    catch(e){_recLogErr('captureStream error: '+e.message);return;}
    try{_recMR=new MediaRecorder(stream,{mimeType:_recMime});}
    catch(e){_recLogErr('Recorder init error: '+e.message);return;}

    _recChunks=[];_recActive=true;
    _recMR.ondataavailable=function(e){if(e.data&&e.data.size>0)_recChunks.push(e.data);};
    _recMR.onstop=_recSave;
    _recMR.onerror=function(e){_recLogErr('Recorder error: '+(e.error?e.error.message:e));_recCleanupUI();};
    _recMR.start(1000);

    // Fetch frames from /capture (same-origin, no CORS issue)
    _recBusy=false;
    (function fetchFrame(){
      if(!_recActive)return;
      if(_recBusy){_recFetchTimer=setTimeout(fetchFrame,REC_INTERVAL_MS);return;}
      _recBusy=true;
      fetch('/capture?r='+Date.now())
        .then(function(r){return r.blob();})
        .then(function(blob){
          const url=URL.createObjectURL(blob);
          const im=new Image();
          im.onload=function(){
            if(_recCanvas.width!==im.naturalWidth||_recCanvas.height!==im.naturalHeight){
              _recCanvas.width=im.naturalWidth;_recCanvas.height=im.naturalHeight;
            }
            _recCtx.drawImage(im,0,0);
            URL.revokeObjectURL(url);
            _recBusy=false;
            if(_recActive)_recFetchTimer=setTimeout(fetchFrame,REC_INTERVAL_MS);
          };
          im.onerror=function(){URL.revokeObjectURL(url);_recBusy=false;if(_recActive)_recFetchTimer=setTimeout(fetchFrame,REC_INTERVAL_MS*2);};
          im.src=url;
        })
        .catch(function(){_recBusy=false;if(_recActive)_recFetchTimer=setTimeout(fetchFrame,REC_INTERVAL_MS*4);});
    })();

    _recStartTime=Date.now();
    const btn=document.getElementById('rec-btn'),ind=document.getElementById('rec-indicator');
    if(btn){btn.classList.add('recording');btn.innerHTML='&#9209; STOP';}
    if(ind)ind.classList.add('active');
    _recTimerInt=setInterval(function(){
      const d=document.getElementById('rec-timer-display');
      if(d)d.textContent=_recFmt(Date.now()-_recStartTime);
    },500);
    log('Recording started (~8 fps via /capture)','ok');
  }

  function _stopRec(){
    _recActive=false;
    clearTimeout(_recFetchTimer);_recFetchTimer=null;
    if(_recMR&&_recMR.state!=='inactive')_recMR.stop();
    _recCleanupUI();
  }
  function _recCleanupUI(){
    clearInterval(_recTimerInt);_recTimerInt=null;
    const btn=document.getElementById('rec-btn'),ind=document.getElementById('rec-indicator'),d=document.getElementById('rec-timer-display');
    if(btn){btn.classList.remove('recording');btn.innerHTML='&#9210; REC';}
    if(ind)ind.classList.remove('active');
    if(d)d.textContent='00:00';
  }
  function _recSave(){
    const dur=_recFmt(Date.now()-_recStartTime);
    if(!_recChunks.length){log('Recording stopped — no data captured','warn');return;}
    const ext=_recMime.startsWith('video/mp4')?'mp4':'webm';
    const blob=new Blob(_recChunks,{type:_recMime});
    const url=URL.createObjectURL(blob);
    const a=document.createElement('a');a.href=url;
    a.download='32sc_'+new Date().toISOString().slice(0,19).replace(/:/g,'-')+'.'+ext;
    document.body.appendChild(a);a.click();document.body.removeChild(a);
    URL.revokeObjectURL(url);_recChunks=[];
    log('Recording saved — '+dur,'ok');
  }

  // ── SYSTEM_LOG
  function log(msg,type){
    const out=document.getElementById('log-output');if(!out)return;
    const now=new Date();
    const ts=now.getHours().toString().padStart(2,'0')+':'+
              now.getMinutes().toString().padStart(2,'0')+':'+
              now.getSeconds().toString().padStart(2,'0');
    const entry=document.createElement('div');
    entry.className='log-entry'+(type?' '+type:'');
    entry.textContent='['+ts+'] '+msg;
    out.appendChild(entry);out.scrollTop=out.scrollHeight;
  }
  function toggleLog(){
    const out=document.getElementById('log-output'),tog=document.getElementById('log-toggle');
    const open=out.style.display!=='none';
    out.style.display=open?'none':'block';
    tog.textContent=open?'▸':'▾';
  }

  // ── Live controller graphic ───────────────────────────────────
  function _cgSet(id,on,color){
    const e=document.getElementById(id); if(!e)return;
    if(on){ e.style.fill=color||'#00ffe7'; e.style.filter='drop-shadow(0 0 4px '+(color||'#00ffe7')+')'; }
    else  { e.style.fill=''; e.style.filter='none'; }
  }
  function updateControllerGraphic(gp){
    const ls=document.getElementById('cg-lstick'), rs=document.getElementById('cg-rstick');
    if(!ls||!rs)return;
    if(!gp){
      ls.setAttribute('transform','translate(0,0)'); rs.setAttribute('transform','translate(0,0)');
      ls.style.fill=''; rs.style.fill='';
      ['cg-a','cg-b','cg-x','cg-y','cg-lb','cg-rb','cg-dup','cg-ddown','cg-dleft','cg-dright','cg-back','cg-start']
        .forEach(function(id){_cgSet(id,false);});
      var l0=document.getElementById('cg-lt'),r0=document.getElementById('cg-rt');
      if(l0)l0.setAttribute('opacity','0.15'); if(r0)r0.setAttribute('opacity','0.15');
      return;
    }
    const ax=gp.axes||[], b=gp.buttons||[];
    const pr=function(i){return b[i]&&(b[i].pressed||b[i].value>0.5);};
    ls.setAttribute('transform','translate('+((ax[0]||0)*8).toFixed(1)+','+((ax[1]||0)*8).toFixed(1)+')');
    rs.setAttribute('transform','translate('+((ax[2]||0)*8).toFixed(1)+','+((ax[3]||0)*8).toFixed(1)+')');
    _cgSet('cg-a',pr(0),'#39ff14'); _cgSet('cg-b',pr(1),'#ff3c5f');
    _cgSet('cg-x',pr(2),'#00aaff'); _cgSet('cg-y',pr(3),'#ffd600');
    _cgSet('cg-lb',pr(4)); _cgSet('cg-rb',pr(5));
    _cgSet('cg-back',pr(8)); _cgSet('cg-start',pr(9));
    _cgSet('cg-dup',pr(12)); _cgSet('cg-ddown',pr(13)); _cgSet('cg-dleft',pr(14)); _cgSet('cg-dright',pr(15));
    ls.style.fill = pr(10) ? '#00ffe7' : '';   // L3 stick click
    rs.style.fill = pr(11) ? '#00ffe7' : '';   // R3 stick click
    const lt=b[6]?b[6].value:0, rt=b[7]?b[7].value:0;
    var lte=document.getElementById('cg-lt'); if(lte)lte.setAttribute('opacity',(0.15+0.85*lt).toFixed(2));
    var rte=document.getElementById('cg-rt'); if(rte)rte.setAttribute('opacity',(0.15+0.85*rt).toFixed(2));
  }

  setInterval(function(){
    const _gpAll=getXboxGamepad();
    updateControllerGraphic(_gpAll);   // live mirror of the physical controller (any mode)
    if(inputMode==='joystick'){
      const gp=_gpAll;if(gp){
        axisMappings.forEach(function(m){
          const src=AXIS_SOURCES.find(a=>a.id===m.axisId);
          setSlider(m.servo,axisToServo255(getAxisValue(gp,m.axisId),src&&src.isTrigger,m.invert,m.deadzone));
        });
        buttonMappings.forEach(function(m){
          const src=BUTTON_SOURCES.find(b=>b.id===m.btnId);if(!src)return;
          const btn=gp.buttons[src.btnIdx],pressed=btn&&(btn.pressed||btn.value>0.5);
          const wasPressed=!!btnPrevState[m._id],risingEdge=pressed&&!wasPressed;
          btnPrevState[m._id]=pressed;if(!pressed&&!risingEdge)return;
          const srv=m.servo;let cur=parseInt(sliders[srv].value);
          if(m.action==='set'&&risingEdge)setSlider(srv,m.value);
          if(m.action==='center'&&risingEdge)setSlider(srv,127);
          if(m.action==='min'&&risingEdge)setSlider(srv,0);
          if(m.action==='max'&&risingEdge)setSlider(srv,255);
          if(m.action==='toggle'&&risingEdge){const k='t'+m._id;btnToggleState[k]=!btnToggleState[k];setSlider(srv,btnToggleState[k]?255:0);}
          if(m.action==='inc'&&pressed)setSlider(srv,cur+(m.value||3));
          if(m.action==='dec'&&pressed)setSlider(srv,cur-(m.value||3));
        });
      }
    }
    // ── Key held: inc/dec (always active, regardless of inputMode) ──
    if(keysHeld.size){
      keyMappings.forEach(function(m){
        if(!m.key||!keysHeld.has(m.key))return;
        const srv=m.servo,cur=parseInt(sliders[srv].value);
        if(m.action==='inc')setSlider(srv,cur+(m.value||3));
        if(m.action==='dec')setSlider(srv,cur-(m.value||3));
      });
    }
  },50);

  // ── PERSISTENT CONFIG ─────────────────────────────────────────
  // All page settings (mappings, input mode, camera params) are saved to the
  // controller (/savecfg → NVS) and restored on load (/loadcfg).
  // Endpoints + LCD rotation persist via their own NVS paths.
  function collectConfig(){
    return { v:1, axisMappings:axisMappings, buttonMappings:buttonMappings,
             keyMappings:keyMappings, inputMode:inputMode, cam:camState };
  }
  function saveConfig(){
    if(_loadingCfg)return;
    clearTimeout(_cfgTimer);
    _cfgTimer=setTimeout(function(){
      fetch('/savecfg',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},
        body:'cfg='+encodeURIComponent(JSON.stringify(collectConfig()))})
        .then(function(r){ if(!r.ok) log('Settings save failed ('+r.status+')','err'); })
        .catch(function(){ log('Settings save failed (network)','err'); });
    },500);
  }
  // Apply the non-resolution sensor params (quality, effect, brightness, etc.).
  function _applyCamSensorParams(){
    var c=camState; if(!c||!_cameraPresent)return;
    ['quality','effect','awb_mode','night','brightness','contrast','saturation','sharpness','denoise','hmirror','vflip']
      .forEach(function(p){ if(c[p]!=null) fetch('/set?'+p+'='+encodeURIComponent(c[p])).catch(function(){}); });
  }
  function _applyCamFromState(){
    var c=camState; if(!c)return;
    // 1. Reflect saved values in the UI controls immediately.
    var e=document.getElementById('cam-effect'); if(e&&c.effect!=null)e.value=c.effect;
    var a=document.getElementById('cam-awb');    if(a&&c.awb_mode!=null)a.value=c.awb_mode;
    [['quality','cam-quality','cam-qual-val'],['brightness','cam-brightness','cam-bright-val'],
     ['contrast','cam-contrast','cam-contrast-val'],['saturation','cam-saturation','cam-sat-val'],
     ['sharpness','cam-sharpness','cam-sharp-val'],['denoise','cam-denoise','cam-denoise-val']].forEach(function(t){
      if(c[t[0]]==null)return;
      var s=document.getElementById(t[1]); if(s)s.value=c[t[0]];
      var v=document.getElementById(t[2]); if(v)v.textContent=c[t[0]];
    });
    if(c.night!=null){_nightOn=!!(+c.night);var nb=document.getElementById('cam-night');if(nb){nb.textContent=_nightOn?'ON':'OFF';nb.classList.toggle('on',_nightOn);}}
    if(c.hmirror!=null){_mirrorOn=!!(+c.hmirror);var mb=document.getElementById('cam-hmirror');if(mb){mb.textContent='MIRROR '+(_mirrorOn?'ON':'OFF');mb.classList.toggle('on',_mirrorOn);}}
    if(c.vflip!=null){_flipOn=!!(+c.vflip);var fb=document.getElementById('cam-vflip');if(fb){fb.textContent='FLIP '+(_flipOn?'ON':'OFF');fb.classList.toggle('on',_flipOn);}}
    if(c.res){var r=document.getElementById('cam-res');if(r)r.value=c.res; currentRes=c.res; _autoResApplied=true;}
    if(c.rotate!=null){_camRotate=parseInt(c.rotate,10)||0;var ro=document.getElementById('cam-rotate');if(ro)ro.value=String(_camRotate);}
    applyCamRotation();   // SPILCD_SDCARD addition: always, so restored mirror/flip apply too
    // The firmware cold-boots the camera at the saved resolution, so NO page-load
    // reinit is needed — apply the sensor params immediately (no 5–10 s lag).
    _applyCamSensorParams();
  }
  function applyConfig(){
    fetch('/loadcfg').then(function(r){return r.json();}).then(function(cfg){
      if(!cfg||typeof cfg!=='object')return;
      _loadingCfg=true;
      try{
        if(Array.isArray(cfg.axisMappings)){axisMappings=[];cfg.axisMappings.forEach(function(m){
          axisMappings.push({_id:nextAxisId++,axisId:m.axisId||'LX',servo:m.servo||0,invert:!!m.invert,deadzone:m.deadzone!=null?m.deadzone:0.08});});}
        if(Array.isArray(cfg.buttonMappings)){buttonMappings=[];cfg.buttonMappings.forEach(function(m){
          buttonMappings.push({_id:nextBtnId++,btnId:m.btnId||'A',servo:m.servo||0,action:m.action||'set',value:m.value!=null?m.value:255});});}
        if(Array.isArray(cfg.keyMappings)){keyMappings=[];cfg.keyMappings.forEach(function(m){
          keyMappings.push({_id:nextKeyId++,key:m.key||'',servo:m.servo||0,action:m.action||'set',value:m.value!=null?m.value:255});});}
        renderAxisMappings();renderButtonMappings();renderKeyMappings();
        if(cfg.cam){camState=Object.assign({},cfg.cam);_applyCamFromState();}
        if(cfg.inputMode==='joystick'&&gamepadConnected&&inputMode!=='joystick')toggleInputMode();
        log('Settings loaded: '+axisMappings.length+' axis / '+buttonMappings.length+' button / '+keyMappings.length+' key mappings','ok');
      }catch(e){ log('Settings load error: '+e,'err'); }
      _loadingCfg=false;
    }).catch(function(){_loadingCfg=false;});
  }
  applyConfig();

</script>
<script>
  // ── THERMAL FEED (SPILCD_SDCARD addition) ─────────────────────
  // Polls /thermal (raw 32x24 temperatures, tenths of a degree, already
  // oriented like the LCD) and paints it here: coloured with the LCD's
  // ramp, scaled up with smoothing, centre crosshair, readouts, and a spot
  // temperature under the pointer. Polling stops while the tab is hidden,
  // which also lets the board stop scanning the sensor for us.
  //
  // View options (this browser only, remembered in localStorage):
  //   MIRROR / FLIP / ROT  transform the whole panel image.
  //   ENHANCED             the LCD's Enhanced Thermal view, rebuilt here from
  //                        the camera feed: thermal colours inside the
  //                        calibrated rectangle (/thermal "fus"), the camera's
  //                        edges embossed onto them, dimmed grey camera
  //                        around it. Same constants as fuseFrame() in the
  //                        firmware. Needs the LIVE FEED camera running.
  (function(){
    var cv=document.getElementById('thermal-canvas'); if(!cv)return;
    var ctx=cv.getContext('2d'),
        st=document.getElementById('thermal-status'),
        spot=document.getElementById('thermal-spot'),
        cam=document.getElementById('stream');
    // Source image, before mirror/flip/rotate: 32x24 thermal, or 320x240 fused.
    var small=document.createElement('canvas'); small.width=32; small.height=24;
    var sctx=small.getContext('2d'), simg=sctx.createImageData(32,24);
    var big=document.createElement('canvas'); big.width=320; big.height=240;
    var bctx=big.getContext('2d', {willReadFrequently:true}), bimg=bctx.createImageData(320,240);
    var SRC_W=320, SRC_H=240;                  // logical source size, both modes
    // Same five stops as thermRGB() in the firmware, so both screens agree.
    var STOPS=[[0,0,0],[60,0,120],[200,40,60],[255,160,0],[255,255,220]];
    // fuseFrame() constants: FUS_EDGE_GAIN, FUS_EDGE_MAX, FUS_CTX_DIM.
    var EDGE_GAIN=3, EDGE_MAX=235, CTX_DIM=110;
    var DEG='°', last=null, sLo=null, sHi=null, pending=false;

    // ── view state ──
    //  m/f/r  plain thermal view: mirror / flip / rotate the whole panel.
    //  am/af/ar  ENHANCED alignment: mirror / flip / rotate ONLY the thermal
    //            layer inside the calibration box, to match how the sensor
    //            sits relative to the camera. Kept apart so switching modes
    //            never disturbs the other mode's setting.
    var view={m:false,f:false,r:0,e:false,am:false,af:false,ar:0};
    try{ var sv=JSON.parse(localStorage.getItem('thermView')||'null');
         if(sv){ view.m=!!sv.m; view.f=!!sv.f; view.r=(sv.r|0)%360; view.e=!!sv.e;
                 view.am=!!sv.am; view.af=!!sv.af; view.ar=(sv.ar|0)%360; } }catch(e){}
    function saveView(){ try{ localStorage.setItem('thermView',JSON.stringify(view)); }catch(e){} }
    // The orientation of the whole picture. ENHANCED is the camera picture
    // with thermal laid on it, so as a whole it is oriented exactly like
    // LIVE FEED (the page's own _mirrorOn/_flipOn/_camRotate); its thermal
    // layer is then lined up inside the box with am/af/ar (see thermUV).
    function fused(){ return view.e&&camReady(); }
    // Box position (0..1 across, 0..1 down) -> grid (u 0..31, v 0..23),
    // undoing the ENHANCED alignment: un-rotate, then un-mirror/flip —
    // the reverse of "mirror/flip, then rotate", the order used everywhere
    // else. A quarter turn maps the 32x24 grid into the box's own shape;
    // the calibration box ("fus") is what sets the final fit.
    function thermUV(a,b){
      var x=a-0.5, y=b-0.5, t;
      switch(view.ar){
        case 90:  t=x; x=y;  y=-t; break;
        case 180: x=-x; y=-y;      break;
        case 270: t=x; x=-y; y=t;  break;
      }
      if(view.am)x=-x; if(view.af)y=-y;
      return [(x+0.5)*31,(y+0.5)*23];
    }
    function xf(){
      if(fused()) return { m: typeof _mirrorOn!=='undefined'&&_mirrorOn,
                           f: typeof _flipOn!=='undefined'&&_flipOn,
                           r: typeof _camRotate!=='undefined'?(_camRotate|0)%360:0 };
      return view;
    }
    function syncButtons(){
      function on(id,b){ var el=document.getElementById(id); if(el) el.classList.toggle('on',b); }
      // The three buttons show (and change) whichever mode is active.
      var m=view.e?view.am:view.m, f=view.e?view.af:view.f, r=view.e?view.ar:view.r;
      on('th-mirror',m); on('th-flip',f); on('th-rot',r!==0); on('th-enh',view.e);
      var rb=document.getElementById('th-rot'); if(rb) rb.innerHTML='ROT '+r+'&deg;';
      ['th-mirror','th-flip','th-rot'].forEach(function(id){
        var el=document.getElementById(id); if(!el)return;
        el.title=view.e?'ENHANCED: turns the thermal layer to line up with the camera'
                       :'Turns the thermal view';
      });
    }
    // Quarter turns swap the panel to portrait. Only resized on a change:
    // setting a canvas's size clears it.
    function sizeCanvas(r){
      var side=(r%180)!==0, w=side?240:320, h=side?320:240;
      if(cv.width!==w||cv.height!==h){ cv.width=w; cv.height=h; }
      var ar=side?'3 / 4':'4 / 3';
      cv.style.aspectRatio=ar; st.style.aspectRatio=ar;
    }
    window.thermalView=function(k){
      if(k==='e') view.e=!view.e;
      else if(view.e){                     // ENHANCED: align the thermal layer
        if(k==='m') view.am=!view.am;
        else if(k==='f') view.af=!view.af;
        else if(k==='r') view.ar=(view.ar+90)%360;
      } else {                             // plain: orient the whole view
        if(k==='m') view.m=!view.m;
        else if(k==='f') view.f=!view.f;
        else if(k==='r') view.r=(view.r+90)%360;
      }
      saveView(); syncButtons(); render();
    };

    function ramp(t,lo,hi){
      var u=(t-lo)/(hi-lo); u=u<0?0:u>1?1:u; u*=4;
      var i=Math.min(3,Math.floor(u)), f=u-i, a=STOPS[i], b=STOPS[i+1];
      return [a[0]+(b[0]-a[0])*f, a[1]+(b[1]-a[1])*f, a[2]+(b[2]-a[2])*f];
    }
    // Readout colour: the value's own palette colour, lifted toward white so
    // the cold end (near black) is still legible on the dark panel.
    function textCol(t){
      var c=ramp(t,sLo,sHi);
      return 'rgb('+(((c[0]+255)/2)|0)+','+(((c[1]+255)/2)|0)+','+(((c[2]+255)/2)|0)+')';
    }
    function setVal(id,v,u){
      var el=document.getElementById(id); if(!el)return;
      el.textContent=v.toFixed(1)+DEG+u; el.style.color=textCol(v);
    }
    function status(txt,searching){
      st.textContent=txt; st.className=searching?'searching':'';
    }
    function camReady(){ return cam && cam.complete && cam.naturalWidth>0 && cam.style.display!=='none'; }

    // Bilinear sample of the grid at fractional (u,v) in 0..31 x 0..23.
    function sample(d,u,v){
      var i0=Math.min(30,Math.max(0,u|0)), j0=Math.min(22,Math.max(0,v|0)), fu=u-i0, fv=v-j0;
      var r0=j0*32+i0, r1=r0+32;
      return (d[r0]*(1-fu)*(1-fv)+d[r0+1]*fu*(1-fv)+d[r1]*(1-fu)*fv+d[r1+1]*fu*fv)/10;
    }

    function buildPlain(d){
      var px=simg.data;
      for(var i=0;i<768;i++){
        var c=ramp(d.d[i]/10,sLo,sHi);
        px[i*4]=c[0]; px[i*4+1]=c[1]; px[i*4+2]=c[2]; px[i*4+3]=255;
      }
      sctx.putImageData(simg,0,0);
      return small;
    }

    // The firmware's fuseFrame(), on the 320x240 camera frame.
    function buildFused(d){
      bctx.drawImage(cam,0,0,320,240);
      var src=bctx.getImageData(0,0,320,240).data, W=320, H=240;
      var L=new Uint8Array(W*H);
      for(var p=0,q=0;p<W*H;p++,q+=4) L[p]=(src[q]*77+src[q+1]*150+src[q+2]*29)>>8;
      var f=d.fus||[20,34,280,172], fx=f[0], fy=f[1], fw=f[2], fh=f[3];
      var su=fw>1?31/(fw-1):0, svv=fh>1?23/(fh-1):0, out=bimg.data;
      for(var y=0;y<H;y++){
        var inRow=y>=fy&&y<fy+fh, v=(y-fy)*svv;
        for(var x=0;x<W;x++){
          var o=(y*W+x)*4, edge=0;
          if(y>0&&y<H-1&&x>0&&x<W-1){
            var u0=(y-1)*W+x, c0=y*W+x, d0=(y+1)*W+x;
            var gx=(L[u0+1]+2*L[c0+1]+L[d0+1])-(L[u0-1]+2*L[c0-1]+L[d0-1]);
            var gy=(L[d0-1]+2*L[d0]+L[d0+1])-(L[u0-1]+2*L[u0]+L[u0+1]);
            edge=((Math.abs(gx)+Math.abs(gy))*EDGE_GAIN)>>2; if(edge>EDGE_MAX)edge=EDGE_MAX;
          }
          if(inRow&&x>=fx&&x<fx+fw){
            var g2=thermUV(fw>1?(x-fx)/(fw-1):0, fh>1?(y-fy)/(fh-1):0);
            var c=ramp(sample(d.d,g2[0],g2[1]),sLo,sHi), k=(255-edge)/256;
            out[o]=c[0]*k; out[o+1]=c[1]*k; out[o+2]=c[2]*k;
          } else {
            var g=(L[y*W+x]*CTX_DIM)>>8; out[o]=out[o+1]=out[o+2]=g;
          }
          out[o+3]=255;
        }
      }
      bctx.putImageData(bimg,0,0);
      // Thin cyan box round the thermal-covered region, as on the LCD.
      bctx.strokeStyle='#00ffff'; bctx.lineWidth=1;
      bctx.strokeRect(fx+0.5,fy+0.5,fw-1,fh-1);
      return big;
    }

    function render(){
      var t=xf(); sizeCanvas(t.r);
      if(!last){ ctx.clearRect(0,0,cv.width,cv.height); return; }
      var fu=fused(), img=fu?buildFused(last):buildPlain(last);
      if(view.e&&!fu) status('ENHANCED NEEDS THE CAMERA — SHOWING THERMAL',false);
      else st.className='hidden';
      ctx.save();
      ctx.imageSmoothingEnabled=true; ctx.imageSmoothingQuality='high';
      // Same order as the LIVE FEED's CSS "rotate() scale()": mirror/flip in
      // image space first, then turn.
      ctx.translate(cv.width/2,cv.height/2);
      ctx.rotate(t.r*Math.PI/180);
      ctx.scale(t.m?-1:1, t.f?-1:1);
      ctx.drawImage(img,-SRC_W/2,-SRC_H/2,SRC_W,SRC_H);
      ctx.restore();
      var cx=cv.width/2, cy=cv.height/2;
      ctx.strokeStyle='rgba(255,255,255,0.85)'; ctx.lineWidth=1.5;
      ctx.beginPath();
      ctx.moveTo(cx-10,cy); ctx.lineTo(cx-3,cy); ctx.moveTo(cx+3,cy); ctx.lineTo(cx+10,cy);
      ctx.moveTo(cx,cy-10); ctx.lineTo(cx,cy-3); ctx.moveTo(cx,cy+3); ctx.lineTo(cx,cy+10);
      ctx.stroke();
    }
    // Coalesce: a thermal frame and a camera frame arriving together draw once.
    function requestRender(){ if(pending)return; pending=true;
      requestAnimationFrame(function(){ pending=false; render(); }); }

    function onData(d){
      var lo=d.min, hi=d.max;
      if(hi-lo<2){var m=(lo+hi)/2; lo=m-1; hi=m+1;}
      // Ease the palette range, as the LCD does, so a still scene does not shimmer.
      if(sLo===null){sLo=lo; sHi=hi;}
      sLo+=(lo-sLo)*0.3; sHi+=(hi-sHi)*0.3;
      last=d;
      setVal('th-max',d.max,d.unit);     setVal('th-centre',d.centre,d.unit);
      setVal('th-min',d.min,d.unit);     setVal('th-amb',d.ambient,d.unit);
      requestRender();
    }
    function poll(){
      if(document.hidden){ setTimeout(poll,1000); return; }
      fetch('/thermal',{cache:'no-store'}).then(function(r){return r.json();}).then(function(d){
        if(d.ok){ onData(d); }
        else {
          last=null; render();
          status(d.state==='starting' ? 'STARTING...'
               : d.state==='stalled'  ? 'THERMAL CAMERA STALLED'
               : d.state==='disabled' ? 'THERMAL NOT BUILT'
               :                        'NO THERMAL CAMERA — SEARCHING',
                 d.state!=='disabled');
        }
      }).catch(function(){ status('THERMAL OFFLINE',true); })
        .then(function(){ setTimeout(poll,250); });   // ~4 fps, the sensor's own rate
    }
    // Enhanced mode also redraws on every camera frame, so outlines move at
    // camera rate. addEventListener leaves the page's own img.onload alone.
    if(cam) cam.addEventListener('load',function(){ if(view.e&&last) requestRender(); });

    // Spot temperature under the pointer: undo the view transform back to
    // source coordinates, then to the grid (through the rectangle when fused).
    cv.addEventListener('pointermove',function(e){
      if(!last){ spot.style.display='none'; return; }
      var r=cv.getBoundingClientRect();
      var px=(e.clientX-r.left)/r.width*cv.width-cv.width/2,
          py=(e.clientY-r.top)/r.height*cv.height-cv.height/2;
      var x=xf(), a=-x.r*Math.PI/180, ca=Math.cos(a), sa=Math.sin(a);
      var qx=px*ca-py*sa, qy=px*sa+py*ca;
      if(x.m)qx=-qx; if(x.f)qy=-qy;
      var sx=qx+SRC_W/2, sy=qy+SRC_H/2, t=null;
      if(fused()){
        var f=last.fus||[20,34,280,172];
        if(sx>=f[0]&&sx<f[0]+f[2]&&sy>=f[1]&&sy<f[1]+f[3])
        { var g=thermUV((sx-f[0])/(f[2]-1),(sy-f[1])/(f[3]-1)); t=sample(last.d,g[0],g[1]); }
      } else {
        var gx=Math.max(0,Math.min(31,Math.floor(sx/SRC_W*32))),
            gy=Math.max(0,Math.min(23,Math.floor(sy/SRC_H*24)));
        t=last.d[gy*32+gx]/10;
      }
      if(t===null){ spot.style.display='none'; return; }
      spot.textContent=t.toFixed(1)+DEG+last.unit;
      spot.style.left=(e.clientX-r.left)+'px'; spot.style.top=(e.clientY-r.top)+'px';
      spot.style.display='block';
    });
    cv.addEventListener('pointerleave',function(){ spot.style.display='none'; });
    syncButtons();
    poll();
  })();
</script>
</body>
</html>
)rawliteral";
