var crtads=0;
var crtads970=0;
var uw=crtg_content.split(/; */);
var uwlen=uw.length;
for (var i=0;i<uwlen;i++){
	if(typeof(criteo_params.rta970)!='undefined' && uw[i]==criteo_params.rta970) {
		crtads970=1;
	}
	if(uw[i]==criteo_params.rta){
		crtads=1;
	}
}

if(!criteo_params.no_criteo && typeof(criteo970_allow)!='undefined' && criteo970_allow && crtads970 && u_data[6]!='1') {
} else if(!criteo_params.no_criteo && crtads){
	if(u_data[6]=='1') crtads970 = 0 ;
	document.getElementById('bannerY'+ucoz_rndid).value=400;
	document.getElementById('bannerX'+ucoz_rndid).value=240;
	document.MAX_ct0 ='INSERT_CLICK_URL';
	var m3_u = (location.protocol=='https:'?'https://cas.criteo.com/delivery/ajs.php?':'http://cas.criteo.com/delivery/ajs.php?');
	var m3_r = Math.floor(Math.random()*99999999999);
	document.write ("<scr"+"ipt type='text/javascript' src='"+m3_u);
	document.write ("zoneid=" + criteo_params.zoneid);
	document.write ('&amp;cb=' + m3_r);
	if (document.MAX_used != ',') document.write ("&amp;exclude=" + document.MAX_used);
	document.write (document.charset ? '&amp;charset='+document.charset : (document.characterSet ? '&amp;charset='+document.characterSet : ''));
	document.write ("&amp;loc=" + escape(window.location));
	if (document.context) document.write ("&context=" + escape(document.context));
	if ((typeof(document.MAX_ct0) != 'undefined') && (document.MAX_ct0.substring(0,4) == 'http')) {
		document.write ("&amp;ct0=" + escape(document.MAX_ct0));
	}
	if (document.mmm_fo) document.write ("&amp;mmm_fo=1");
	document.write ("'></scr"+"ipt>");
	document.write('<scr'+'ipt type="text/javascript">new Image().src = "http://counter.yadro.ru/hit;audit_criteo_narod?r"+escape(document.referrer)+((typeof(screen)=="undefined")?"":";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+";"+Math.random();</scr'+'ipt>');
} else if(u_data[6]=='1') {
	crtads970 = 0 ;
	document.getElementById('bannerY'+ucoz_rndid).value=400;
	document.getElementById('bannerX'+ucoz_rndid).value=240;
	var between_type="adi";
	document.write('<scr'+'ipt type="text/javascript" src="http://cache.betweendigital.com/sections/138716.js"></scr'+'ipt>');
} else if(ucoz_prerollenable) {
	document.getElementById('wrapperX'+ucoz_rndid).value=0;
	document.getElementById('wrapperY'+ucoz_rndid).value=0;
	document.getElementById('dV'+ucoz_rndid).style.overflow='';
	document.write('<style id="hideAdBlock240x400">#'+ucoz_rndid+' .a-buttons.green-but.a-clock, #'+ucoz_rndid+' .a-buttons.blue-but.a-check, #'+ucoz_rndid+' td[valign="top"]{display: none!important}</style>');
	document.write('<scr'+'ipt type="text/javascript" src="http://c.morgdm.ru/?src=ucfs&s_subid='+(u_data[5] ? 'videobtmwrpwork' : 'videobtmwrp')+'"></scr'+'ipt>');
	if(u_data[7]=='1')
		document.write('<scr'+'ipt type="text/javascript" src="http://c.morgdm.ru/?src=ucfs&s_subid=cat1"></scr'+'ipt>');
	else if(u_data[8]=='1')
		document.write('<scr'+'ipt type="text/javascript" src="http://c.morgdm.ru/?src=ucfs&s_subid=trrnt"></scr'+'ipt>');
	else
		document.write('<scr'+'ipt type="text/javascript" src="http://c.morgdm.ru/?src=ucfs"></scr'+'ipt>');
	new Image().src = "//counter.yadro.ru/hit;preroll_total_narod?r"+ escape(document.referrer)+((typeof(screen)=="undefined")?"":";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+";"+Math.random();
	uPreroll_setcookie() ;
} else {
	document.getElementById('bannerY'+ucoz_rndid).value=400;
    document.getElementById('bannerX'+ucoz_rndid).value=240;
	if(user_country == 'ru'){
		document.addEventListener('DOMContentLoaded' , uShowRuAdBanner) ;
	} else {		
		var script_ads = document.createElement("script");
		script_ads.src = 'http://rot.spotsniper.ru/?src=ujs1';
		script_ads.async = false;    		    			
		document.getElementsByTagName("head")[0].appendChild(script_ads);
		new Image().src = "//counter.yadro.ru/hit;supersniper_sng_narod?r"+ escape(document.referrer)+((typeof(screen)=="undefined")?"":";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+";"+Math.random();
	}
}

function uShowRuAdBanner() {

	var bnr_iframe = document.createElement('iframe');
	bnr_iframe.setAttribute('frameborder', '0');
	bnr_iframe.setAttribute('style', 'width:240px;height:400px;');
	document.getElementById('mainadsdv' + ucoz_rndid).appendChild(bnr_iframe);
	bnr_iframe.contentWindow.document.open();
	bnr_iframe.contentWindow.document.write('<html><head>');
	bnr_iframe.contentWindow.document.write(
		"<script>"+
		"onBtwIframeMessage = function(e) {"+
			"document.getElementsByTagName('iframe')[0].contentWindow.postMessage(e.data , '*');"+
		"};"+
		"if (typeof window.addEventListener != 'undefined') {"+
			"window.addEventListener('message', onBtwIframeMessage, false);"+
		"} else if (typeof window.attachEvent != 'undefined') {"+
			"window.attachEvent('onmessage', onBtwIframeMessage);"+
		"}"+
		"</script>"
	);
	bnr_iframe.contentWindow.document.write('<style>body{margin:0;}</style>');
	bnr_iframe.contentWindow.document.write('</head><body>');

	bnr_iframe.contentWindow.document.write('<script>between_type="adi";</script>');
	bnr_iframe.contentWindow.document.write("<scr"+"ipt type='text/javascript' src='http://cache.betweendigital.com/sections/95306.js'></scr"+"ipt>");
	new Image().src = "//counter.yadro.ru/hit;betweennarod?r"+ escape(document.referrer)+((typeof(screen)=="undefined")?"":";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+";"+Math.random();

	bnr_iframe.contentWindow.document.write('</body></html>');
	bnr_iframe.contentWindow.document.close();
}

document.addEventListener('DOMContentLoaded' , function(){
	//jQuery и uwnd на статику народа
	if (typeof jQuery == 'undefined') {
		var scrpt = document.createElement('script');
		scrpt.src = 'http://'+ucoz_server+'.ucoz.net/src/jquery-1.7.2.js';
		scrpt.onload = function(){
			var scrpt2 = document.createElement('script');
			scrpt2.src = 'http://'+ucoz_server+'.ucoz.net/src/uwnd.js';
			document.head.appendChild(scrpt2);
		}
		document.head.appendChild(scrpt);
	} else {
		if (typeof _uWnd == 'undefined') {
			var scrpt = document.createElement('script');
			scrpt.src = 'http://'+ucoz_server+'.ucoz.net/src/uwnd.js';
			document.head.appendChild(scrpt);
		}
	}
});

var onBetweenMessage = function(e) { 
	if(e.data == 'needsupersnipervars') {
		var frame = document.getElementById('mainadsdv'+ucoz_rndid).getElementsByTagName('iframe')[0] ;
		text = 'supersnipervars|'+ucoz_server+'|'+ucoz_rndid+'|'+user_country+'|'+window.location.hostname ;
		if(frame) frame.contentWindow.postMessage(text , '*');
	}
};
if (typeof window.addEventListener != 'undefined') {
	window.addEventListener('message', onBetweenMessage, false);
} else if (typeof window.attachEvent != 'undefined') {
	window.attachEvent('onmessage', onBetweenMessage);
}
