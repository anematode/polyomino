var loader = new THREE.CubeTextureLoader();
loader.setPath('src/textures/' );

var textureCube = loader.load([
	'px.jpg', 'px.jpg',
	'px.jpg', 'px.jpg',
	'px.jpg', 'px.jpg'
]);

var cubeMaterial = new THREE.MeshBasicMaterial( { color: 0xffffff, envMap: textureCube } );
var geometry = new THREE.BoxGeometry(1, 1, 1);
geometry.translate(- 0.5, - 0.5, - 0.5);

function createCube(x, y, z) {
  var cube = new THREE.Mesh(geometry, cubeMaterial);
  cube.position.x += x;
  cube.position.y += y;
  cube.position.z += z;

  return cube;
}

renderer = new THREE.WebGLRenderer({antialias: true});
renderer.setSize(window.innerWidth, window.innerHeight);

camera = new THREE.PerspectiveCamera(70, window.innerWidth / window.innerHeight, 1, 1000);

// create the Scene
scene = new THREE.Scene();

scene.add(createCube(3, 4, 5));

container = document.createElement('div');
document.body.appendChild(container);
container.appendChild(renderer.domElement);


var controls = new THREE.OrbitControls( camera );

camera.position.set(0, 20, 100);
controls.update();

controls.target.x = 0;
controls.target.y = 0;
controls.target.z = 0;

var light = new THREE.DirectionalLight( 0xffffff );
light.position.set(1, 1, 1);
scene.add(light);

var light = new THREE.DirectionalLight( 0x002288 );
light.position.set( -1, -1, -1 );
scene.add(light);

var light = new THREE.AmbientLight( 0x222222 );
scene.add(light);

scene.background = new THREE.Color( 0xbbbbbb );
scene.fog = new THREE.FogExp2( 0xddcccc, 0.002 );

window.onresize = function() {
	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();

	renderer.setSize(window.innerWidth, window.innerHeight);
}

function animate() {
	render();

	requestAnimationFrame(animate);
  controls.update();
}

function render() {
  renderer.render(scene, camera);
}

animate()