/*
This is empty on purpose! Your code to build the resume will go here.
$("#main").append("Kevin Liu");
 */

var bio = {
	"name" : "Kevin Liu",
	"role" : "software engineering manager and leader",
	"contacts" : {
		"mobile": "908-675-7390",
		"email": "kl7902@gmail.com",
		"github": "kliu17",
		"twitter": "#liu_kevin",
		"location": "Edison, NJ"
	},
	"welcomeMessage": "welcome to my page",
	"skills":["C++","java","javascript","Python","Scrum","DevOps"],
	"bioPic": "images/kliu.jpg"
}

var education = {
	"schools": [
		{
		"name": "MASSACHUSETTS INSTITUTE OF TECHNOLOGY",
		"city": "Cambridge, MA, USA",
		"degree": "Master Degree",
		"majors": ["Management and Engineering"]
		},
		{
                "name": "VICTORIA UNIVERSITY",
                "city": "Melbourne, Victoria, Australia",
                "degree": "PhD Degree",
                "majors": ["Computer Science"]
                }
	],
	"onlineCourses": [
		{
		"title": "fullstack web development",
		"school": "udacity",
		"dates" : 2017
		}
	]
}


var work = {
	"jobs": [
		{
		"employer": "Crestron INC",
		"title": "Senior Manager, Application and User Interface",
		"dates": "June 2013 - Present",
		"location": "Rockleigh, NJ",
		"description": "IoT application and UI engineering manager to develop home and office automation applications, user interfaces (web, iOS/Android mobile apps), cloud services supporting consumer-oriented smart objects and intelligent services. Responsible for platform architecture and design. Drive engineering resources and processes to deliver product releases with quality. Developed intelligent automation applications of lights, shades, climate, security, media, energy monitor, scheduling service, dashboard of data analytics, recommendations."
		},
		{
                "employer": "EMC Corporation",
                "title": "Software Engineering Manager",
                "dates": "January 2006 - May 2013",
		"location": "Berkeley Heights, NJ",
                "description": "Technical manager & lead for ITOps cloud platform (Object-Oriented, high-throughput ITIL framework for IT operation management for virtualized data centers, cloud providers) software development, architecture, technical strategy. Led code & design reviews. Interfaced with customers, partners for requirements, use cases. Developed virtualization, SDN root cause analysis features and alerting web services for fault & service management across storage, network, server, VM, containers, applications."
                },
		{
                "employer": "T-Mobile",
                "title": "Lead System Engineer",
                "dates": "September 2004 - January 2006",
		"location": "Parsippany, NJ",
                "description": "Lead a project group of software and system engineers to develop, deploy web-based configuration and customer service order management solutions for large-scale production wireless networks. Developed fault management process & standard as part of T-Mobile data governance strategy, and alarm correlation system for GSM, and GPRS & VoIP networks. Worked as a technical lead to design and implement an integrated web-based network service management system for Operation Center."
                },
                { 
                "employer": "Elematics INC", 
                "title": "Senior Software Engineer",
                "dates": "November 2011 - September 2004",
		"location": "New York, NY",
                "description": "Designed, implemented resource reservation signaling, routing protocol for scalable control plane for wired, wireless networks. Designed, implemented service provisioning algorithms for reconfigurable optical networks."
                },                { 
                "employer": "Bellcore/Telcordia Technologies (formerly Bell Communications Research)", 
                "title": "Member of Technical Staff",
                "dates": "March 1998 - October 2011",
		"location": "Red Bank, NJ",
                "description": "Designed and implemented network control and management & business-support software systems and traffic engineering algorithms for telecom networks. Developed query parallel processing algorithms for distributed databases."
                }
	]
}

var projectObj = {
        "projects": [
                {
                "title": "System Design and Scalability",
                "description": "systen design and scalability discussions and topics at Github",
		"href": "https://github.com/checkcheckzz/system-design-interview#tips"
                },
                {
                "title": "Design Pattern",
                "description": "OO design patterns and anti-patterns",
		"href": "https://sourcemaking.com/design-patterns-and-tips"
                },
		{
                "title": "Algorithm",
                "description": "common algorithms review",
                "href": "http://www.geeksforgeeks.org/top-algorithms-and-data-structures-for-competitive-programming/"
                },
		{
                "title": "C++ Language Reference",
                "description": "C++ language reference including STL",
                "href": "http://www.cplusplus.com/reference/stl/"
                },
                {
                "title": "C++ Data Structures and Algorithms",
                "description": "C++ data structure and algorithms cheat sheet",
                "href": "https://github.com/gibsjose/cpp-cheat-sheet/blob/master/Data%20Structures%20and%20Algorithms.md"
                },

                {
                "title": "JavaScript @W3",
                "description": "JavaScript, JQuery, HTML, CSS W3 tutorial and reference",
                "href": "https://www.w3schools.com/js/"
                },
                {
                "title": "Java Interview",
                "description": "Java Interview questions at banks",
                "href": "http://javadecodedquestions.blogspot.sg/2012/01/java-concurrency.html"
                },
                {
                "title": "SQL Outer Join",
                "description": "SQL Inner Join vs. Outer Join",
                "href": "http://www.programmerinterview.com/index.php/database-sql/inner-vs-outer-joins/"
                },
                {
                "title": "SQL Interview Questions",
                "description": "SQL interview questins",
                "href": "https://dwbi.org/database/sql/72-top-20-sql-interview-questions-with-answers"
                }
        ]
}

var formattedHeaderName = HTMLheaderName.replace("%data%",bio.name);
$("#header").append(formattedHeaderName);
var formattedHeaderRole = HTMLheaderRole.replace("%data%",bio.role);
$("#header").append(formattedHeaderRole);
var formattedBioPic = HTMLbioPic.replace("%data%",bio.bioPic);
$("#header").append(formattedBioPic);
var formattedWelcomeMsg = HTMLwelcomeMsg.replace("%data%",bio.welcomeMessage);
$("#header").append(formattedWelcomeMsg);

var formattedMobile = HTMLmobile.replace("%data%",bio.contacts.mobile);
$("#topContacts").append(formattedMobile);
$("#footerContacts").append(formattedMobile);
var formattedEmail = HTMLemail.replace("%data%",bio.contacts.email);
$("#topContacts").append(formattedEmail);
$("#footerContacts").append(formattedEmail);
var formattedGitHub = HTMLgithub.replace("%data%",bio.contacts.github);
$("#topContacts").append(formattedGitHub);
$("#footerContacts").append(formattedGitHub);
var formattedTwitter = HTMLtwitter.replace("%data%",bio.contacts.twitter);
$("#topContacts").append(formattedTwitter);
$("#footerContacts").append(formattedTwitter);
var formattedLocation = HTMLlocation.replace("%data%",bio.contacts.location);
$("#topContacts").append(formattedLocation);
$("#footerContacts").append(formattedLocation);

if (bio.skills.length > 0) {
	$("#header").append(HTMLskillsStart);
	var formattedSkill=HTMLskills.replace("%data%",bio.skills[0]);
	$("#skills").append(formattedSkill);
	formattedSkill=HTMLskills.replace("%data%",bio.skills[1]);
        $("#skills").append(formattedSkill);
	formattedSkill=HTMLskills.replace("%data%",bio.skills[2]);
        $("#skills").append(formattedSkill);
	formattedSkill=HTMLskills.replace("%data%",bio.skills[3]);
        $("#skills").append(formattedSkill);
	formattedSkill=HTMLskills.replace("%data%",bio.skills[4]);
        $("#skills").append(formattedSkill);
	formattedSkill=HTMLskills.replace("%data%",bio.skills[5]);
        $("#skills").append(formattedSkill);
}

function displayEducation() {
  for (school in education.schools) {
        $("#education").append(HTMLschoolStart);
        var formattedName=HTMLschoolName.replace("%data%",education.schools[school].name);
        var formattedDegree=HTMLschoolDegree.replace("%data%",education.schools[school].degree);
	var formattedNameDegree=formattedName+formattedDegree;
        $(".education-entry:last").append(formattedNameDegree);

        var formattedCity=HTMLschoolLocation.replace("%data%",education.schools[school].city);
        $(".education-entry:last").append(formattedCity);

        var formattedMajor=HTMLschoolMajor.replace("%data%",education.schools[school].majors);;
        $(".education-entry:last").append(formattedMajor);
  }
}

function displayProject() {
	for (proj in projectObj.projects) {
        $("#projects").append(HTMLprojectStart);
        var formattedProjHref=HTMLprojectTitle.replace("#",projectObj.projects[proj].href);
        var formattedProjName=formattedProjHref.replace("%data%",projectObj.projects[proj].title);
        var formattedProjDescription=HTMLprojectDescription.replace("%data%",projectObj.projects[proj].description);
        $(".project-entry:last").append(formattedProjName);
        $(".project-entry:last").append(formattedProjDescription);
	}
}


function displayWork() {
  for (job in work.jobs) {
	$("#workExperience").append(HTMLworkStart);
	var formattedEmployer=HTMLworkEmployer.replace("%data%",work.jobs[job].employer);
	var formattedTitle=HTMLworkTitle.replace("%data%",work.jobs[job].title);
	var formattedEmployerTitle=formattedEmployer + formattedTitle;
	$(".work-entry:last").append(formattedEmployerTitle);

	var formattedDates=HTMLworkDates.replace("%data%",work.jobs[job].dates);
	var formattedWorkLocation=HTMLworkLocation.replace("%data%",work.jobs[job].location);
	var formattedWorkDatesLocation=formattedDates + formattedWorkLocation;
	$(".work-entry:last").append(formattedWorkDatesLocation);

	var formattedDesc = HTMLworkDescription.replace("%data%",work.jobs[job].description);
	$(".work-entry:last").append(formattedDesc);
  }
}

function locationizer(work_obj) {
	var locationArray = [];
	for (job in work_obj.jobs) {
		var newLocation=work_obj.jobs[job].location;
		locationArray.push(newLocation);
	}
	return locationArray;

}

function inName(name) {
	name = name.trim().split(" ");
	/* console.log(name); */
	name[1]=name[1].toUpperCase();
	name[0]=name[0].slice(0,1).toUpperCase()+name[0].slice(1).toLowerCase();
	return name[0]+" "+name[1];
}

console.log(locationizer(work));
displayEducation();
displayWork();
displayProject();
$("#main").append(internationalizeButton);
$("#mapDiv").append(googleMap);
