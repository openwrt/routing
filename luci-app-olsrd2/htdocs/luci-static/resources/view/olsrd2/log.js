'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'log', _('OONF Logging'));
		s.anonymous = true;
		s.addremove = false;

		o = s.option(form.Flag, "syslog", _("syslog are boolean options that activate or deactivate the syslog Logging Target."), "");
		o.optional = true;
		o.datatype = "bool";
		o = s.option(form.Flag, "stderr", _("stderr are boolean options that activate or deactivate the stderr Logging Target."), "");
		o.optional = true;
		o.datatype = "bool";
		o = s.option(form.Value, "file", _("file asks for a filename for logging output"),"Filename");
		o.rmempty = false;
		o.optional = true;
		o.placeholder = "/tmp/olsrd2.log";
		o.datatype = "string";
		o = s.option(form.Value, "debug", _("debug ask for a list of Logging Sources that will be logged by the OONF Core Logging Targets."));
		o.rmempty = false;
		o.optional = true;
		o.datatype = "string";
		o = s.option(form.Value, "info", _("info ask for a list of Logging Sources that will be logged by the OONF Core Logging Targets."));
		o.rmempty = false;
		o.optional = true;
		o.datatype = "string";

		return m.render();
	}
});
