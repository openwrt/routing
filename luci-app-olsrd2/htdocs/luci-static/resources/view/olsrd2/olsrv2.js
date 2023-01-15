'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'olsrv2', _('the OLSRv2 implementation including the OLSRv2 API for other plugins.'));
		s.anonymous = true;
		s.addremove = false;

		o = s.option(form.Value, "tc_interval", _("defines the time between two TC messages."), "s");
		o.optional = true;
		o.placeholder = 5.0;
		o.datatype = "ufloat";
		o = s.option(form.Value, "tc_validity", _("tc_validity defines the validity time of the TC messages."), "s");
		o.optional = true;
		o.placeholder = 300.0;
		o.datatype = "ufloat";
		o = s.option(form.Value, "forward_hold_time", _("forward_hold_time defines the time until the router will forget an entry in its forwarding duplicate database."), "s");
		o.optional = true;
		o.placeholder = 300.0;
		o.datatype = "ufloat";
		o = s.option(form.Value, "processing_hold_time", _("processing_hold_time defines the time until the router will forget an entry in its processing duplicate database."), "s");
		o.optional = true;
		o.placeholder = 300.0;
		o.datatype = "ufloat";
		o = s.option(form.DynamicList, "routable", _("routable defines the ACL which declares an IP address routable. Other IP addresses will not be included in TC messages."), "ip6prefix, ip4prefix, default_accept, default_reject");
		o.datatype = "string";
//TODO
//svc.datatype = "or(negm(ip6addr), negm(ip4addr), 'default_accept', 'default_reject')"
//modules/luci-base/htdocs/luci-static/resources/cbi.js:545
//			negm: function() {
//			return this.apply('or', this.value.replace(/^[ \t]*-[ \t]*/, ''), arguments);
//		},
	//modules/luci-base/luasrc/cbi/datatypes.lua:51
//function negm(v, ...)
//	return _M['or'](v:gsub("^%s*-%s*", ""), ...)
//end
		o.optional = true;
		o = s.option(form.DynamicList, "originator", _("originator defines the ACL which declares a valid originator IP address for the router."), "ip6prefix, ip4prefix, default_accept, default_reject");
		o.datatype = "string";
//TODO
//svc.datatype = "or(negm(ip6addr), negm(ip4addr), 'default_accept', 'default_reject')"
//modules/luci-base/htdocs/luci-static/resources/cbi.js:545
//			negm: function() {
//			return this.apply('or', this.value.replace(/^[ \t]*-[ \t]*/, ''), arguments);
//		},
	//modules/luci-base/luasrc/cbi/datatypes.lua:51
//function negm(v, ...)
//	return _M['or'](v:gsub("^%s*-%s*", ""), ...)
//end
		o.optional = true;

		return m.render();
	}
});
