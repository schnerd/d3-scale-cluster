var Jasmine = require('jasmine');
var JasmineConsoleReporter = require('jasmine-console-reporter');

var jasmine = new Jasmine();
jasmine.loadConfig({
	spec_dir: 'spec',
	spec_files: [
		'**/*Common[sS]pec.js', '**/*NodeModern[sS]pec.js',
	],
	helpers: [
		'helpers/**/*.js'
	],
	stopSpecOnExpectationFailure: false,
	random: false
});

jasmine.addReporter(new JasmineConsoleReporter({
	colors: 1,           // (0|false)|(1|true)|2 
	cleanStack: 1,       // (0|false)|(1|true)|2|3 
	verbosity: 4,        // (0|false)|1|2|(3|true)|4 
	listStyle: 'indent', // "flat"|"indent" 
	activity: false
}));

jasmine.execute();
