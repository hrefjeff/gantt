document.writeln('Hello, world!');

divider(20);

var empty_object = {};

var msThang = {

	"first-name" : "Morgan\u00E9",
	middle_name  : "msThang",
	last_name    : "Burcham"

};

document.writeln(msThang['first-name']);
document.writeln(msThang.last_name);

// for default vals, use ||
// Basically saying undefined, or "blah"
document.writeln(msThang.middle_name || "default");
document.writeln(msThang['middle_name'] || "default");

divider('22');

// update

msThang["first-name"] = "Missy";
msThang.last_name = "Elliot";

document.writeln(msThang['first-name']);
document.writeln(msThang.last_name);

divider(23);

// 10_30 (Programming languages example)
document.writeln("a".charCodeAt(0));

function divider(section){

		document.writeln('****************'+ section +'****************');

}

// ASCII code



// Freeze --- c++ const?
// From the Javascript: the difinitive guide

Object.freeze(msThang);

msThang['first-name'] = 'SomeChange';
document.writeln(msThang['first-name']);
document.writeln('Wow. No change o___o');