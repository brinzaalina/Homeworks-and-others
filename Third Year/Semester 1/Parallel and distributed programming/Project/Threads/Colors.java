import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Colors {
    /*
    colorsNumber: int representing number of colors
    colors: map with (key,value) pairs where key(int) is the code of the color and value(string) is the name of the color
     */
    private int colorsNumber;
    private Map<Integer,String> colors;

    //constructor
    public Colors(int n){
        this.colorsNumber = n;

        colors = new HashMap<>();
        for (int code=0; code< n ; code++){
            colors.put(code, "");
        }
    }

    //add a new color
    public void addColor( int code, String color){
        colors.put(code, color);
    }

    //get a  map of codes and colors for a list of given codes
    public Map<Integer, String> getColorsForCodes(List<Integer> codes) {
        Map<Integer,String> result = new HashMap<>();

        for(int i =0;i < codes.size();i++){
            String color = colors.get(codes.get(i));
            result.put(i, color);
        }
        return result;
    }

    //getters and setters
    public int getColorsNumber() { return colorsNumber; }

    public void setColorsNumber(int colorsNumber) { this.colorsNumber = colorsNumber; }

    public Map<Integer, String> getColors() { return colors; }

    public void setColors(Map<Integer, String> colors) { this.colors = colors; }

    @Override
    public String toString() {
        return "Colors{" +
                "colorsNumber=" + colorsNumber +
                ", colors=" + colors +
                '}';
    }
}
