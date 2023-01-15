'use strict';
'require view';
'require ui';
'require rpc';
'require poll';

var callgetData = rpc.declare({
	object: 'status.olsrd2',
	method: 'getNeighbors'
});

function createTable(data) {
    let tableData = [];
    data.neighbors.forEach(row => {
		let hostname = E('a',{ 'href': 'https://' + row.hostname + '/cgi-bin-olsrd2-neigh.html'},row.hostname);
		let orginator = E('a',{ 'href': 'https://[' + row.originator + ']/cgi-bin-olsrd2-neigh.html'},row.originator);
        tableData.push([
            hostname,
            orginator,
            row.lladdr,
            row.interface,
            row.metric_in,
            row.metric_in_raw
        ])
    });
    return tableData;
};

return view.extend({
	title: _('OLSRD2 mesh neighbors'),
	handleSaveApply: null,
	handleSave: null,
	handleReset: null,


	render: function(data) {

		var tr = E('table', { 'class': 'table' });
		tr.appendChild(E('tr', { 'class': 'tr cbi-section-table-titles' }, [
			E('th', { 'class': 'th left' }, [ 'Hostname' ]),
			E('th', { 'class': 'th left' }, [ 'Orginator' ]),
			E('th', { 'class': 'th left' }, [ 'MAC' ]),
			E('th', { 'class': 'th left' }, [ 'Interface' ]),
			E('th', { 'class': 'th left' }, [ 'Metric' ]),
			E('th', { 'class': 'th left' }, [ 'raw' ])
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
