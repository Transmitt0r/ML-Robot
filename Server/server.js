const express = require('express');
const app = express();
const axios = require('axios');
const esp = "http://192.168.178.67";

app.use(express.static('public'));

app.get('/', function(req, res) {
	res.send(index.html);
});

app.get('/forward', function(req, res) {
	axios.get(esp + "/forward")
		.then(function (response) {
			res.send(response.data);
		});
});

app.get('/backward', function(req, res) {
	axios.get(esp + "/backward")
		.then(function (response) {
			res.send(response.data);
		});
});

app.get('/left', function(req, res) {
	axios.get(esp + "/left")
		.then(function (response) {
			res.send(response.data);
		});
});

app.get('/right', function(req, res) {
	axios.get(esp + "/right")
		.then(function (response) {
			res.send(response.data);
		});
});

// App listens on port 5000
app.listen(5000);