'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'mesh', _('mesh configuration section'));
		s.anonymous = true;
		s.addremove = false;
		o = s.option(form.Value, "port", _("port defines the UDP port number of the RFC5444 socket."), "1-65535");
		o.optional = true;
		o.placeholder = 269;
		o.datatype = "range(1,65535)";
		o = s.option(form.Value, "ip_proto", _("ip_proto defines the IP protocol number that can be used for RFC5444 communication."), "1-255");
		o.optional = true;
		o.placeholder = 138;
		o.datatype = "range(1,255)";
		o = s.option(form.Value, "aggregation_interval", _("aggregation_interval defines the time the local RFC5444 implementation will keep messages to aggregate them before creating a new RFC5444 packet to forward them."), ">0.1 s");
		o.optional = true;
		o.placeholder = 1.0;
		o.datatype = "and(min(0.1), ufloat)";

		return m.render();
	}
});
