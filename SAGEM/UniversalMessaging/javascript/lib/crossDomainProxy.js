
/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
var clientWindow = null;
var clientOrigin = null;
var xhr = new XMLHttpRequest();

var sessionID = getUrlParameter("sessionID");
var proxyID = getUrlParameter("proxyID");
var validOrigins = getUrlParameter("validOrigins").split(",");

var expired = getUrlParameter("expired");

var iFrame = null;
var source = null;

var isClosed = false;
var debugMode = false;

function clientMessageHandler(e) {
    if (!isValidOrigin(e.origin)) return;
    clientOrigin = e.origin;
    clientWindow = e.source;
    var messageComponents = JSON.parse(e.data);
    var action = messageComponents[1];
    var values = messageComponents.slice(2);
    if (action == "createForeverIFrame") {
        createForeverIFrame(values);
    } else if (action == "createEventSource") {
        createEventSource(values);
    } else if(action == "abort"){
        isClosed = true;
        xhr[action].apply(xhr, values);
        if(iFrame !== null){
            if(iFrame.close){
                iFrame.close();
            }
        }
        if(source !== null){
            source.close();
        }
    } else {
        xhr[action].apply(xhr, values);
    }
}
if (!expired) {

    window.addEventListener("message", clientMessageHandler);
    
    xhr.onreadystatechange = function(){
        try {
            clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "change", xhr.responseText, xhr.readyState, xhr.status]), clientOrigin);
        } catch(err) {
            // Do nothing
        }
    };

}

function onMessage(jsonString) {
        // Streaming IFrame
        try {
            clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "iframe", JSON.stringify(jsonString)]), clientOrigin);
        } catch(err) {
            // Do nothing
        }
}
function errorCB() {
    try {
        clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "iFrame_close"]), clientOrigin);
    }catch(err){
    }

    try{
        if(navigator.appName == "Microsoft Internet Explorer"){
            while (iFrame.hasChildNodes()) {
                iFrame.removeChild(iFrame.lastChild);
            }
        } else{
            while (iFrame.hasChildNodes()) {
                var tmp = iFrame.removeChild(iFrame.lastChild);
                for (var prop in tmp) {
                    delete tmp[prop];
                }
            }
        }
        iFrame.parentWindow.removeChild(iFrame);
    }catch(err){
    }
    try { 
        iFrame.parentWindow.document.removeChild(iFrame);
    } catch(err) {
    }
}

function onHTMLFileMessage(m) {
    try {
        // we stringify m because the realm is outputting an object to window.parent.onMessage for iframe clients,
        // while note that with websocket for instance it is passing the object as a string (ie wrapped in ").
        clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "iframe", JSON.stringify(m)]), clientOrigin);

    } catch(err) {
        // Do nothing
    }
}


function onEventSourceMessage(jsonString) {
    try {
        if (jsonString) {
            clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "sse", jsonString]), clientOrigin);
        }
    } catch(err) {
        // Do nothing
    }
}

function onIframeMessage(jsonString) {
try {
if (jsonString) {
clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "iframe", jsonString]), clientOrigin);
}
} catch(err) {
// Do nothing
}
}

function start(){
    window.parent.postMessage(JSON.stringify([proxyID, sessionID, "init"]), "*"); // Safe to post to any target here, as these were target-supplied variables.
}
start();


function createXHR() {
    // this function should create an XHR proxy only if one is required rather than always creating one.
}

function createForeverIFrame(url) {

url = url.join("");
    if (iFrame === null && !isClosed) {
        if (document.createElement) {
            var element = document.getElementById("NVLSubFrame");
            if (element) {
                element.setAttribute("src", url);
                iFrame = element;
            } else {
                //console.log("Iframe does not exist, so creating new one " + url);
                //the onload below allows browsers to know when a iframe document is fully loaded (connection closed)
                var iframeSubHTML = "<iframe id=\"NVLSubFrame\" onload=\"try{errorCB()}catch(e){}\" src=\"" + url + "\" style=\"";
                iframeSubHTML += 'border:1px;';
                iframeSubHTML += 'width:0px;';
                iframeSubHTML += 'height:0px;';
                iframeSubHTML += '"><\/iframe>';

                if (window.ActiveXObject) {
                    this.htmlfile = new ActiveXObject('htmlfile');
                    this.htmlfile.open();
                    this.htmlfile.write('<html></html>');
                    this.htmlfile.close();

                    // set our various callbacks:
                    this.htmlfile.parentWindow.onMessage = onHTMLFileMessage;
                    this.htmlfile.parentWindow.errorCB = errorCB;

                    var iframeC = this.htmlfile.createElement('div');
                    this.htmlfile.body.appendChild(iframeC);
                    iframeC.innerHTML += iframeSubHTML;
                    iFrame = this.htmlfile;
                } else {
                    document.getElementById("SUBFRAMEHOLDER").innerHTML = iframeSubHTML;
                    iFrame = {};
                    iFrame.document = {};
                    iFrame.document.location = {};
                    iFrame.document.location.iframe = document.getElementById('NVLSubFrame');
                    iFrame.document.location.replace = function (location) {
                        this.iframe.src = location;
                    };
                }
            }
        }
    }
}

function createEventSource(url) {
    url = url.join("");

    source = new EventSource(url);

    source.onmessage = function (sse) {
        var json = sse.data;
        onEventSourceMessage(json);
    };

    source.onerror = function(err) {
        if (err.readyState == EventSource.CLOSED) {
            clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "SSE_close"]), clientOrigin);
        } else {
            clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "SSE_error"]), clientOrigin);
        }
        source.close();
    };


}

function isValidOrigin(messageOrigin) {
    messageOrigin = getCanonicalOrigin(messageOrigin).toUpperCase();
    for (var i = 0; i < validOrigins.length; i++) {
        if (messageOrigin == validOrigins[i].toUpperCase()){
            return true;
            }
    }
    return false;
}

function getCanonicalOrigin(url) {
    url = url.match(/^https?:\/\/[^\/]+/)[0];
    if (!url.match(/:[0-9]+$/)) {
        if (url.match(/^https:/)) {
            url += ":443";
        } else {
            url += ":80";
        }
    }
    return url;
}

function getUrlParameter( name ) {
    name = name.replace(/[\[]/,"\\[").replace(/[\]]/,"\\]");
    var regexS = "[\\?&]"+name+"=([^&#]*)";
    var regex = new RegExp( regexS );
    var results = regex.exec( window.location.href );
    if( results === null )
        return "";
    else
        return unescape(results[1]);
}

function c(data) {
    try {
        clientWindow.postMessage(JSON.stringify([proxyID, sessionID, "change", data, 4, 200]), clientOrigin);
    } catch(err) {
        // Do nothing
    }
}
