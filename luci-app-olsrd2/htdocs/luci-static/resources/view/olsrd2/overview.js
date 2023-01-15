'use strict';
'require view';
'require ui';
'require rpc';
'require poll';

var callgetVersion = rpc.declare({
	object: 'status.olsrd2',
	method: 'getVersion'
});
var callgetLan = rpc.declare({
	object: 'status.olsrd2',
	method: 'getLan'
});

function createTable(data) {
    let tableData = [];
	if ( data && data[0] && data[0].version && data[0].version[0] ) {
		if ( data[0].version[0].version_text != undefined ) {
			tableData.push([_('Version'),data[0].version[0].version_text]);
		}
		if ( data[0].version[0].version_commit != undefined) {
			tableData.push([_('GIT commit'),data[0].version[0].version_commit]);
		}
	}
	if ( data && data[1] && data[1].lan && data[1].lan[0] ) {
		if ( data[1].lan[0].lan != undefined ) {
			tableData.push([_('LAN IP'),data[1].lan[0].lan]);
		}
		if ( data[1].lan[0].domain != undefined) {
			tableData.push([_('Domain'),data[1].lan[0].domain]);
		}
		if ( data[1].lan[0].domain_metric != undefined) {
			tableData.push([_('Domain metric'),data[1].lan[0].domain_metric]);
		}
		if ( data[1].lan[0].domain_metric_out != undefined) {
			tableData.push([_('Domain metric outgoing'),data[1].lan[0].domain_metric_out]);
		}
		if ( data[1].lan[0].domain_metric_out_raw != undefined) {
			tableData.push([_('domain_metric_out_raw'),data[1].lan[0].domain_metric_out_raw]);
		}
		if ( data[1].lan[0].domain_distance != undefined) {
			tableData.push([_('Domain distance'),data[1].lan[0].domain_distance]);
		}
	}
    return tableData;
}

return view.extend({
	title: _('Version'),
	handleSaveApply: null,
	handleSave: null,
	handleReset: null,

	render: function() {

		var tr = E('table',{ 'class': 'table'});
		tr.appendChild(E('tr', { 'class': 'tr cbi-section-table-titles' }, [
			E('th', { 'class': 'th left' }),
			E('th', { 'class': 'th left' })
		]));
        poll.add(() => {
            Promise.all([
				callgetVersion(),
				callgetLan()
            ]).then((results) => {
                cbi_update_table(tr, createTable(results));
            })
        }, 30);

		return tr;
	}

});
