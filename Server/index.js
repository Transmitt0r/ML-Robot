const express = require('express');
const app = express();
const bodyParser = require('body-parser');

// body parser allows us to parse json if we need to
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Sensor-Data Post route
app.post('/input', function(req, res) {
	console.log("Data received: " + req.body.data);
	// return received data as response
	res.send(req.body.data);
});

// App listens on port 5000
app.listen(5000);