var IGNORE_DIRECTORY = 'config'
  , GIT_DIRECTORY = 'config.git'
  , fs = require( 'fs' )
  , join = require( 'path' ).join
  , cp = require( 'child_process' );
  
function execute( cmd, cwd, done ) {
  console.log( ':node test$ ' + cmd ); 
  var p = cp.exec( cmd, { cwd: cwd }, function( err, stdout, stderr ) {
    if (err)
      console.error( stderr ); 
  } ); 
  p.stdout.on( 'data', function( data ) { 
    process.stdout.write( data ); 
  } );
  if (typeof done != 'undefined')
    p.on( 'exit', done ); 
  return p;
}

(function() {

  process.on( 'SIGINT', function() {
    console.log( 'error: SIGINT' );
    process.exit(1);
  } );
  
  fs.readdir( __dirname, function( err, list ) {
    if (err) throw err;
    list.forEach( function( file ) {
      var path = join( __dirname, file ); 

      fs.stat( path, function( err, stat ) {
        if (    stat 
             && stat.isDirectory() 
             && file != IGNORE_DIRECTORY
             && file != GIT_DIRECTORY
             && file != '.svn') {
          console.log( 'testing ' + path + ':' );
          execute( 'make -f ../config/makefile run', path, function() {
            execute( 'make -f ../config/makefile clean', path );
          } );
        }
      } );
    } );
  } );
})();
