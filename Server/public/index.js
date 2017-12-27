const control = new Vue({
    el: '#control',
    data: {
        Direction: "",
        Obstacle: "",
        Light: 0,
    },
    created: function() {
        window.addEventListener('keyup', this.keyCode);
    },
    methods: {
        updateData: function(data) {
            this.Direction = data.direction;
            this.Obstacle = data.obstacle;
            this.Light = data.light;
        },
        keyCode: function(key) {
            if (key.code == "ArrowUp") {
                this.forward();
            } else if (key.code == "ArrowDown") {
                this.backward();
            } else if (key.code == "ArrowLeft") {
                this.left();
            } else if (key.code == "ArrowRight") {
                this.right();
            }
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
        left: function() {
            var self = this;
            axios.get('/left')
                .then(function(response) {
                    console.log("Left");
                    self.updateData(response.data);
                })
        },
        right: function() {
            var self = this;
            axios.get('/right')
                .then(function(response) {
                    console.log("Right");
                    self.updateData(response.data);
                })
        }
    },
})