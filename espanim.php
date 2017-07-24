<?php

/* https://github.com/squix78/esp8266-weather-station/issues/61 */

$anim = $argv[1];
$rotate = isset($argv[2]) && $argv[2]=='rotate' ? " -rotate -90 " : false;
$name = current(explode('.', basename($anim)));

exec("rm png/$name*");
exec("rm str/$name*");

$animInfos = array();
$frameInfos = array();

exec("convert $anim $rotate -verbose info:- > out");
exec("convert $anim $rotate -identify -transparent orange png/$name%02d.png", $animInfos);
//echo file_get_contents('out');
//print_r($animInfos);

//exit;

$total = count($animInfos);

foreach($animInfos as $pos => $info) {
  //echo $info;
  $info = explode(" ", $info);
  $filenameframe = explode('[', $info[0]);
  $filename = $filenameframe[0];
  $framepos = str_replace(']', '', $filenameframe[1]);
  $imgsize = $info[2];
  if($rotate ) {
    $imgsize = explode("=>", $imgsize);
    $imgsize = $imgsize[1];
  }
  $delay = round(str_replace('u', '', $info[7])*1000);

  list($imgwidth, $imgheight) = explode('x', $imgsize);
  $framesizeoffset = explode('+', $info[3]);
  $framesize = current($framesizeoffset);
  list($framewidth, $frameheight) = explode('x', $framesize);
  $offsetleft = $framesizeoffset[1];
  $offsettop  = $framesizeoffset[2];

  $frameInfos[$pos] = array(
    'raw'         => $info,
    'file'        => $filename,
    'frame'       => $framepos,
    'delay'       => $delay,
    'imgwidth'    => $imgwidth,
    'imgheight'   => $imgheight,
    'framewidth'  => $framewidth,
    'frameheight' => $frameheight,
    'offsetleft'  => $offsetleft,
    'offsettop'   => $offsettop
  );

  //print_r($frameInfo);
}
//WindowsXP.gif[0] GIF 128x160 128x160+0+0 8-bit sRGB 128c 6.79KB 0.000u 0:00.010
print_r($frameInfos);

$curdir = getcwd();
chdir('png');
$pngFiles = glob("$name*");
chdir($curdir);

$out = '
#include <pgmspace.h>
';

$switchcase = '

animInfo getAnimInfo'.$name.'() {
  return animInfo{'.count($pngFiles).', 0x0000};
}

frameInfo frame'.$name.'(int id) {
   switch(id) {
';

$frameNum = 0;

foreach($pngFiles as $pos => $pngFile) {
  $frameInfo =  $frameInfos[$pos];
  $outName = current(explode('.', $pngFile));
  $outFile = $outName.'.c';
  $outRgbFile = $outName.'.rgb';
  $cmdout = array();
  $cmd = "php espimage.php inFile=png/$pngFile outFile=str/$outFile width=$frameInfo[imgwidth] height=$frameInfo[imgheight] format=hex";
  exec($cmd, $cmdout);
  $istransparent = false;
  $transparentcolor = '0x0000';
  switch($cmdout[0]) {
    case 'Is Transparent':
      $istransparent = true;
      $transparentcolor = $cmdout[1];
    break;
  }
  //print_r($cmdout);
  //$cmd = "php espimage.php inFile=png/$pngFile outFile=raw/$outRgbFile width=128 height=160";
  //exec($cmd);
  echo "Processing $pngFile: $cmd\n";
  //$switchcase .= "    case $frameNum: return $outName; break;\n";
  $switchcase .= sprintf("    case $frameNum: return frameInfo{\"%s\", %s, %s, %s, %s, %s, %s, %s, %s}; break;\n",
    $frameInfo['file'],
    $frameInfo['frame'],
    $frameInfo['imgwidth'],
    $frameInfo['imgheight'],
    $frameInfo['offsetleft'],
    $frameInfo['offsettop'],
    $istransparent ? 'true' : 'false',
    $transparentcolor,
    $outName
  );

  $out.= '#include "'.$outName.'.c"'."\n";
  $frameNum++;
}


$out .= $switchcase;
$out .= '
   }
};';

file_put_contents("str/$name.h", $out);
