import ddf.minim.*;
import ddf.minim.analysis.*;
 
Minim minim;
AudioPlayer song;
FFT fft;

float angle = 0;
 
void setup()
{
  size(512, 512);
  colorMode(HSB, 360, 100, 100);

  minim = new Minim(this);

  song = minim.loadFile("No_1.mp3", 512);
  song.play();

  fft = new FFT(song.bufferSize(), song.sampleRate());
}
 
void draw(){
  background(0);
  noFill();

  fft.forward(song.mix);
  
  translate(width/2, height/2);
//  stroke(255, 0, 0, 128);

  angle = angle + PI/100;
  rotate(angle);
  println(angle);
  
  stroke(255);
 
  pushMatrix();
  for(int p = 0; p < 18; p++){
    stroke(50 + song.left.get(p)*300, 100, 100);
//    ellipse(0, 0, song.left.get(p)*300, song.left.get(p)*400 +30);
//    rectMode(CENTER);
//    rect(0, 0, song.left.get(p)*300, song.left.get(p)*100);
    for(int i = 0; i < song.left.size() - 1; i++)
    {
      line(i + 4, song.left.get(i)*50, i+1, song.left.get(i+1)*50);
//      println(50 + song.left.get(i)*300);
    }
     
    rotate(PI/9);
  }

  popMatrix();
  
}
