document.write('</div>');
    //if (GDATA[u_data[4]][u_data[0]][1]!='') document.write(GDATA[u_data[4]][u_data[0]][1]);
	document.write('<div id="_u_ablock_bottomlink" style="margin: 0;padding: 0;background: none;"></div>');
    document.write('	</td>'+
(u_data[2]=="1" ? b_v2 : '')+
'    </tr>'+
'    </table>');

function addUcozWrapperLink(place , html) {
	place = place=='top' ? 'top' : 'bottom' ;
	var wrelem = document.getElementById('wrapperY'+u_data[1]) ;
	var linkelem = document.getElementById('_u_ablock_'+place+'link');
	if(!wrelem || !linkelem) return ;
	linkelem.innerHTML = html ;
	var wrH = parseInt(wrelem.value) ;
	wrelem.value = wrH<50 ? wrH+25 : wrH ;
	resizeDiv();
}
if(u_data[0]=='US') {
	document.write('<scr'+'ipt type="text/javascript" src="http://rot.spotsniper.ru/?src=ujs4&s_subid=300topwrp" async></scr'+'ipt>');
	document.write('<scr'+'ipt type="text/javascript" src="http://rot.spotsniper.ru/?src=ujs4&s_subid=300btmwrp" async></scr'+'ipt>');
} else {
	document.write('<scr'+'ipt type="text/javascript" src="http://rot.spotsniper.ru/?src=ujs1&s_subid=240topwrp" async></scr'+'ipt>');
	document.write('<scr'+'ipt type="text/javascript" src="http://rot.spotsniper.ru/?src=ujs1&s_subid=240btmwrp" async></scr'+'ipt>');
}
