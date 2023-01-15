'use strict';
'require view';
'require form';

return view.extend({
	render: function() {
		var m, s, o;

		m = new form.Map('olsrd2', 'OLSRD2 Daemon');

		s = m.section(form.TypedSection, 'global', _('It controls the basic behavior of the OONF core.'));
		s.anonymous = true;
		s.addremove = false;

		o = s.option(form.Flag, "failfast", _("failfast is another boolean setting which can activate an error during startup if a requested plugin does not load or an unknown configuration variable is set."), "");
		o.optional = true;
		o.rmempty = true;
		o.datatype = 'bool';
		o = s.option(form.Value, "pidfile", _("pidfile is used together with the fork option to store the pid of the background process in a file."), "Filename");
		o.optional = true;
		o.rmempty = true;
		o.placeholder = '/var/run/olsrd2.pid';
		o.datatype = 'string';
		o = s.option(form.Value, "lockfile", _("lockfile creates a file on disk and keeps a lock on it as long as the OONF application is running to prevent the application from running multiple times at once."), "Filename");
		o.rmempty = false;
		o.optional = true;
		o.placeholder = "/var/lock/olsrd2";
		o.datatype = "string";

		return m.render();
	}
});
