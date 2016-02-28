if(typeof(crtads970)!="undefined" && crtads970) {
	document.write('<style>#uCrit970_cont{display: inline-block;width: 970px;height: 268px;position: relative;}#uCrit970_close {position: absolute;right: -12px;top: 20px;cursor:pointer;}</style>');
	document.write('<style>.adv-remove {display: block;text-align: center !important;background: url(http://sdev022.ucozmedia.com/ucoz/img/uads/a-buttons-logged.gif) repeat-x !important;padding: 0 10px !important;margin: 0 !important;font: bold 9px/18px \'Tahoma\', \'Arial\' !important;color: #fff !important;text-decoration: none !important;text-transform: uppercase;border-radius: 0 0 3px 3px;}</style>');
	document.write('<div id="uCrit970" style="text-align: center;"><div id="uCrit970_cont">');
	document.write('<img src="http://'+ucoz_server+'.ucoz.net/img/ma/cv.gif" id="uCrit970_close" />');
	document.MAX_ct0 ='INSERT_CLICK_URL';
	var m3_u = (location.protocol=='https:'?'https://cas.criteo.com/delivery/ajs.php?':'http://cas.criteo.com/delivery/ajs.php?');
	var m3_r = Math.floor(Math.random()*99999999999);
	document.write ("<scr"+"ipt type='text/javascript' src='"+m3_u);
	document.write ("zoneid="+criteo_params.zoneid970);
	document.write ('&amp;cb=' + m3_r);
	if (document.MAX_used != ',') document.write ("&amp;exclude=" + document.MAX_used);
	document.write (document.charset ? '&amp;charset='+document.charset : (document.characterSet ? '&amp;charset='+document.characterSet : ''));
	document.write ("&amp;loc=" + escape(window.location).substring(0,1600));
	if (document.context) document.write ("&context=" + escape(document.context));
	if ((typeof(document.MAX_ct0) != 'undefined') && (document.MAX_ct0.substring(0,4) == 'http')) {
		document.write ("&amp;ct0=" + escape(document.MAX_ct0));
	}
	if (document.mmm_fo) document.write ("&amp;mmm_fo=1");
	document.write ("'></scr"+"ipt>");
	document.write ('<div style="position:absolute;bottom:0px;left:0px;text-align:left;width: 100%;z-index: 1;cursor:pointer;" onclick="event.stopPropagation();" id="inbodycont_footer"><a href="javascript://" onclick="new _uWnd(\'UBROWSERDOWNLOAD\',\'Отключение рекламы\',-550,-400,{popup:1,modal:1,resize:0,autosize:0,align:\'justify\'},\'<div id=&quot;ads_window&quot; class=&quot;ads_window&quot;></div><style type=&quot;text/css&quot;>.xw-active, .x-sh{display:none;}</style><script type=&quot;text/javascript&quot; src=&quot;http://cdn.uranupdates.com/popup2/uadsoff6.js&quot;></scr\'+\'ipt>\');return false;" title="Отключить рекламу на всех сайтах системы uCoz" class="adv-remove"><span>Убрать рекламный баннер</span></a></div>');
	document.write('</div></div>');
	document.addEventListener('DOMContentLoaded' , function(){
		document.getElementById('uCrit970_close').addEventListener('click' , function(){
			document.getElementById('uCrit970').remove();
		});
	});
	document.getElementById(ucoz_rndid).style.display='none';
	new Image().src = "http://counter.yadro.ru/hit;criteo_970_250?r"+escape(document.referrer)+((typeof(screen)=="undefined")?"":";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+";"+Math.random();
}