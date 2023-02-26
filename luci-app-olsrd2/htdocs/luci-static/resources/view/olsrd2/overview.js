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
	if ( data && data.version && data.version[0] ) {
		if ( data.version[0].version_text != undefined ) {
			tableData.push([_('OLSRd2 Version'),data.version[0].version_text]);
		}
		if ( data.version[0].version_commit != undefined) {
			tableData.push([_('OLSRd2 GIT commit'),data.version[0].version_commit]);
		}
	}
	tableData.push(['']);
    return tableData;
}

function createTableDomain(data) {
    let tableData = [];
	if ( data && data.lan && data.lan[0] ) {
		data.lan.forEach(row => {
			tableData.push([
				row.lan,
				row.domain,
				row.domain_metric,
				row.domain_metric_out,
				row.domain_metric_out_raw,
				row.domain_distance
			])
		});
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
		var trd = E('table', { 'class': 'table' });
		trd.appendChild(E('trd', { 'class': 'tr cbi-section-table-titles' }, [
			E('th', { 'class': 'th left' }, [ 'LAN IP' ]),
			E('th', { 'class': 'th left' }, [ 'Domain' ]),
			E('th', { 'class': 'th left' }, [ 'Domain Metric' ]),
			E('th', { 'class': 'th left' }, [ 'Domain Metric out' ]),
			E('th', { 'class': 'th left' }, [ 'Domain Metric out' ]),
			E('th', { 'class': 'th left' }, [ 'Domain distance' ])
		]));
        poll.add(() => {
            Promise.all([
				callgetVersion(),
				callgetLan()
            ]).then((results) => {
                cbi_update_table(tr, createTable(results[0]));
                cbi_update_table(trd, createTableDomain(results[1]));
            })
        }, 30);

		return [tr,trd];
	}

});
