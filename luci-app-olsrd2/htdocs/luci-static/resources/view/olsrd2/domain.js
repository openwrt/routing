'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'domain', _('domain configuration section'));
		s.anonymous = true;
		s.addremove = false;
		o = s.option(form.Value, "table", _("table defines the routing table for the local routing entries."), "0-254");
		o.optional = true;
		o.placeholder = 254;
		o.datatype = "range(0,254)";
		o = s.option(form.Value, "protocol", _("protocol defines the protocol number for the local routing entries."), "0-254");
		o.optional = true;
		o.placeholder = 100;
		o.datatype = "range(0,254)";
		o = s.option(form.Value, "distance", _("distance defines the 'metric' (hopcount) of the local routing entries."), "0-254");
		o.optional = true;
		o.placeholder = 2;
		o.datatype = "range(0,254)";
		o = s.option(form.Flag, "srcip_routes", _("srcip_routes defines if the router sets the originator address as the source-ip entry into the local routing entries."), "");
		o.optional = true;
		o.datatype = "bool";

		return m.render();
	}
});
