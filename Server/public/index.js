const control = new Vue({
    el: '#control',
    data: {
    	Direction: "",
    	Obstacle: "",
    	Light: 0,
    },
    methods: {
    	updateData: function(data) {
        	this.Direction = data.direction;
        	this.Obstacle = data.obstacle;
        	this.Light = data.light;
        },
        forward: function() {
        	var self = this;
            axios.get('/forward')
                .then(function(response) {
                    console.log("Forward");
                    self.updateData(response.data);
                })
        },
        backward: function() {
        	var self = this;
            axios.get('/backward')
                .then(function(response) {
                    console.log("Backward");
                    self.updateData(response.data);
                })
        },
        left: function(){
        	var self = this;
            axios.get('/left')
                .then(function(response) {
                    console.log("Left");
                    self.updateData(response.data);
                })
        },
        right: function(){
        	var self = this;
            axios.get('/right')
                .then(function(response) {
                    console.log("Right");
                    self.updateData(response.data);
                })
        }
    },
})