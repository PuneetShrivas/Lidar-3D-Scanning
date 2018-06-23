import java.io.FileWriter;
import java.io.BufferedWriter;
 
void setup() {
 
  try { 
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("C:/Users/Puneet Shrivas/Desktop/L3DS/L3DS/L3DS_processing_sketch/file3.txt", true)));
    out.println("the text");
    out.flush();
    out.close();
  }
  catch (IOException e) {  
    println(e);
  }
 
}
