<?php

/* https://github.com/squix78/esp8266-weather-station/issues/61 */


error_reporting(E_ALL & ~E_NOTICE);

if(count($argv)==1) {
  die("ESPImage 565 Converter\nUsage: php ".basename(__FILE__)." inFile=[input filename] outFile=[output filename] width=[width] height=[height]\n\n");
}

//print_r($argv);

$inFile = null;
$outFile = null;
$width = 0;
$height = 0;
$format = 'binary';


function loadArgv($argv) {
  global $inFile, $outFile, $width, $height, $format;

  foreach ($argv as $arg) {
    $e=explode("=",$arg);
    if(count($e)==2)
        $_GET[$e[0]]=$e[1];
    else
        $_GET[$e[0]]=0;
  }
  extract($_GET);
}


loadArgv($argv);


if($inFile===null) die("No input file specified\n");
if($outFile===null) die("No output file specified\n");
if($width<=0) die("Invalid width\n");
if($height<=0) die("Invalid height\n");

saveRGB565($inFile, $outFile, $width, $height, $format);

function createImageFromFile($filename, $use_include_path = false, $context = null, &$info = null)
{
    if (!$context)
      $context = stream_context_create(array( 'http' => array("timeout" => 7, 'protocol_version' => 1.1, 'header' => array('Connection: close') ) ) );
    // fetches fileconten from url and creates an image ressource by string data
    // if file is not readable or not supportet by imagecreate FALSE will be returnes as $imageRes
    $imageRes = imagecreatefromstring(file_get_contents($filename, $use_include_path, $context));

    if (!$imageRes)
      $imageRes = imagecreatefromstring(file_get_contents("questionmark.png", $use_include_path, $context));
    // export $http_response_header to have this info outside of this function
    if(isset($http_response_header)) $info["http"] = $http_response_header;

    imagepalettetotruecolor($imageRes); // ensure the image is RGB
    return $imageRes;
}

function resizeImage($image, $max_width, $max_height)
{
    $orig_width = imagesx($image);
    $orig_height = imagesy($image);

    $width = $orig_width;
    $height = $orig_height;

    # taller
    if ($height > $max_height) {
        $width = ($width * $max_height) / $height;
        $height = $max_height;
    }

    # wider
    if ($width > $max_width) {
        $height = ($height * $max_width) / $width;
        $width = $max_width;
    }

    $image_p = imagecreatetruecolor($max_width, $max_height);

    imagecopyresampled($image_p, $image, ($max_width-$width)/2, ($max_height-$height)/2, 0, 0,
                                     $width, $height, $orig_width, $orig_height);

    return $image_p;
}

/**
 * converts images to 16-bit RGB565 raw data stream suitable for ILI9341 and similar
 * format:
 *  [ width (uint16) | height (uint16) | pixel stream (uint16 array[width*height]) ]
 *
 * @param [string:  $srcfilename]         url or local path to image file
 * @param [string:  $dstfilename]         local path to save raw stream to
 */
function saveRGB565($srcfilename, $dstfilename, $max_width = 240, $max_height = 320, $format = "binary", $transcolor='0x0000') {
  $image = createImageFromFile($srcfilename);
  $fname = current(explode('.', $dstfilename));
  $oname = end(explode('/', $fname));

  $file_w = fopen($dstfilename, 'w+');

  $width = imagesx($image);
  $height = imagesy($image);

  if ($width > $max_width || $height > $max_height) {
    $image = resizeImage($image, $max_width, $max_height);
    $width = imagesx($image);
    $height = imagesy($image);
  }

  $len = $width*$height;

  $data = array();
  //fwrite( $file_w, pack('n', ) );
  //fwrite( $file_w, pack('n', $height) );

  if($format==='binary') {
    fwrite( $file_w, pack('n', $width) );
    fwrite( $file_w, pack('n', $height) );
  } else {
    $header = '#include <pgmspace.h>'."\n\n".'const unsigned short '.$oname.'['.($height*$width).'] PROGMEM={'."\n";
    fwrite( $file_w, $header);
  }

  $istransparent = false;
  $colorspace = array();

  for ($y = 0; $y < $height; $y++) {
    $y_array = array();
    for ($x = 0; $x < $width; $x++) {
      $rgb = imagecolorat($image, $x, $y);
      //echo $rgb." = ".decbin($rgb),"<br>";
      //$r = ($rgb >> 16) & 0xFF;
      //$g = ($rgb >> 8) & 0xFF;
      //$b = $rgb & 0xFF;
      $transparency = ($rgb >> 24) & 0x7F;
      // opacity*original + (1-opacity)*background = resulting pixel
      // 5-bit transparency
      $r = ((((127-$transparency) * (($rgb >> 16) & 0xFF)) / 127) & 0xF8) << 8; // + $transparency*0x000000; // (black)
      $g = ((((127-$transparency) * (($rgb >> 8) & 0xFF)) / 127) & 0xFC) << 3;  // + $transparency*0x000000; // (black)
      $b = ((((127-$transparency) * (($rgb) & 0xFF)) / 127) ) >> 3;             // + $transparency*0x000000; // (black)

      if($format==='binary') {
        fwrite( $file_w, pack('n', $r | $g | $b) );
      } else {
        //$pix = dechex( $r | $g | $b);
        //$hex = zeropad($pix, 4);
        //echo "Alpha $transparency ($r, $g, $b)\n";
        if($transparency==127) {
          $istransparent = true;
          $transparentcolor = '0x'.str_pad(dechex( $r | $g | $b ), 4, '0', STR_PAD_LEFT);;
          //$r = $transcolor[0];
          //$g = $transcolor[1];
          //$b = $transcolor[2];
          $hex = $transcolor; // '0x'.str_pad(dechex( $r | $g | $b ), 4, '0', STR_PAD_LEFT);
        } else {
          $colorspace["$r $g $b"] = true;
          $hex = '0x'.str_pad(dechex( $r | $g | $b ), 4, '0', STR_PAD_LEFT);
          $colorspace[$hex] = true;
        }
        $at = ($x + $y*$width);
        $comma = $at == $len-1 ? '' : ', ';
        $suffix = $comma.( $at%16==15 ? "\n" : "");
        $out = $hex.$suffix;
        fwrite( $file_w, $out );
      }
    }
  }
  if($format!='binary') {
    fwrite( $file_w, "\n};\n\n");
  }
  //print_r($colors);
  fclose($file_w);

  if($istransparent) {

    $hexcolor = '0x'.str_pad(dechex($transparentcolor[$r] | $transparentcolor[$g] | $transparentcolor[$b]), 4, '0', STR_PAD_LEFT);

    if(isset($colorspace[$hexcolor])) {
      echo " DUH! transparent index is also used as non transparent color, will regenerate";
      // find a free color code
      for($i=0;$i<65536;$i++) {
        $hex = '0x'.str_pad(dechex( $i ), 4, '0', STR_PAD_LEFT);
        if(!isset($colorspace[$hex])) {
          saveRGB565($srcfilename, $dstfilename, $max_width = 240, $max_height = 320, $format = "binary");
          return;
          //break;
        }
      }
      //saveRGB565($srcfilename, $dstfilename, $max_width = 240, $max_height = 320, $format = "binary") 
    }

    echo "Is Transparent";
    echo "\n";
    echo '0x'.str_pad(dechex($transparentcolor[$r] | $transparentcolor[$g] | $transparentcolor[$b]), 4, '0', STR_PAD_LEFT);
    //fwrite( $file_w "bool istransparent = true;\n";
  } else {
    echo "Is NOT Transparent";
    //fwrite( $file_w "bool istransparent = false;\n";
  }

}

