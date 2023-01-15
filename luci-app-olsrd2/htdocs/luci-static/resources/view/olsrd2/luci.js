'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('luci_olsrd2', 'Luci options');

		s = m.section(form.TypedSection, 'olsrd2', _('LUCI'));
		s.anonymous = true;
		s.addremove = false;

		o = s.option(form.Flag, "resolve", _("do Hostname lookup"), "");
		o.datatype = "bool";
		o = s.option(form.Value, "domain", _("optional Public domain forwarding with dnsmasq-full (auth-zone=example.com) on the internetgateway "), "default is olsr");
		o.datatype = "string";

		return m.render();
	}
});
