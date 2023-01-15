'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'lan_import', _('Automatic import of routing tables as locally attached networks.'));
		s.anonymous = true;
		s.addremove = true;
		o = s.option(form.Value, "name", _("Name"), "Text");
		o.datatype = "string";
		o = s.option(form.Value, "interface", _("Interface"), "Name Interface");
		o.datatype = "string";
		o = s.option(form.Value, "table", _("IP Table"), "1-255");
		o.datatype = "range(1,255)";
		o = s.option(form.Value, "protocol", _("IP protocol"), "1-255");
		o.datatype = "range(1,255)";

		return m.render();
	}
});
