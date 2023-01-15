'use strict';
'require view';
'require ui';
'require rpc';
'require poll';

var callgetData = rpc.declare({
	object: 'status.olsrd2',
	method: 'getAttached_network'
});

function createTable(data) {
    let tableData = [];
    data.attached_network.forEach(row => {
		let node = E('a',{ 'href': 'https://' + row.node + '/cgi-bin-olsrd2-neigh.html'},row.node);
        tableData.push([
            node,
            row.attached_net,
            row.attached_net_src,
            row.domain_metric_out
        ])
    });
    return tableData;
}

return view.extend({
	title: _('OLSRD2 networks'),
	handleSaveApply: null,
	handleSave: null,
	handleReset: null,

	render: function(data) {

		var tr = E('table', { 'class': 'table' });
		tr.appendChild(E('div', { 'class': 'tr cbi-section-table-titles' }, [
			E('th', { 'class': 'th left' }, [ 'IP address' ]),
			E('th', { 'class': 'th left' }, [ 'Network' ]),
			E('th', { 'class': 'th left' }, [ 'Source' ]),
			E('th', { 'class': 'th left' }, [ 'Metric' ])
		]));
        poll.add(() => {
            Promise.all([
				callgetData()
            ]).then((results) => {
                cbi_update_table(tr, createTable(results[0]));
            })
        }, 30);
        return tr
	}

});
