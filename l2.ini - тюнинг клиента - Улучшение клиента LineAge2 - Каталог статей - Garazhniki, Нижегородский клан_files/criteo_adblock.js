document.write('<div id="crt_blk_cont" style="text-align: center;width:100%;height:0px;overflow:hidden;display:block;">');
    document.MAX_ct0 ='INSERT_CLICK_URL';
    var m3_u = (location.protocol=='https:'?'https://cas.criteo.com/delivery/ajs.php?':'http://cas.criteo.com/delivery/ajs.php?');
    var m3_r = Math.floor(Math.random()*99999999999);
    document.write ("<scr"+"ipt type='text/javascript' src='"+m3_u);
    document.write ("zoneid="+( typeof(site_type) == 'string' && site_type=='narod' ? '372120':'372119') );
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
document.write('</div>');

window.checkCriteoI = 0 ;
window.checkCriteo = function() {
    $('#crt_blk_cont').children().each(function(i , elem) {
        if(elem.tagName != "SCRIPT") {
            if( $(elem).height()>1 ) {
                $('#crt_blk_cont').css({'height':'auto','overflow':'inherit'});
                checkCriteoI = 1000 ;
            }
        }
    }) ;
    if(window.checkCriteoI++ < 20) setTimeout('checkCriteo()' , 1000) ;
};
document.addEventListener('DOMContentLoaded',function() {
    checkCriteo();
});