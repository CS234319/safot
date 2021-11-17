import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;

public class HilbertCurves {
    private static int currentX = 0;
    private static int currentY = 0;
    private static final ArrayList<int[]> points = new ArrayList<>();
    private static File currentFile = null;
    public enum Direction { UP, RIGHT, DOWN, LEFT }

    private static void begin(String fileName) throws IOException {
        currentFile = new File(fileName);
        currentFile.createNewFile();
        currentX = 0;
        currentY = 0;
        points.clear();
    }

    private static void draw(Direction direction) {
        int x1 = currentX * 30;
        int y1 = currentY * 30;
        currentX += direction == Direction.RIGHT ? 1 : direction == Direction.LEFT ? -1 : 0;
        currentY += direction == Direction.UP ? 1 : direction == Direction.DOWN ? -1 : 0;
        int x2 = currentX * 30;
        int y2 = currentY * 30;
        points.add(new int[]{x1, y1, x2, y2});

    }

    private static void end() throws IOException {
        String currentSvg = "";
        int maxX = 0, maxY = 0, minX = 0, minY = 0;
        for(int[] pointArray : points) {
            int x1 = pointArray[0], y1 = pointArray[1], x2 = pointArray[2], y2 = pointArray[3];
            maxX = Math.max(x1, Math.max(x2, maxX));
            maxY = Math.max(y1, Math.max(y2, maxY));
            minX = Math.min(x1, Math.min(x2, minX));
            minY = Math.min(y1, Math.min(y2, minY));
        }
        for(int[] pointArray : points) {
            int x1 = pointArray[0] - minX, y1 = maxX + minY - pointArray[1], x2 = pointArray[2] - minX, y2 = maxX + minY - pointArray[3];
            currentSvg += "<line x1=\"" + 3*x1 + "\" y1=\"" + 3*y1 + "\" x2=\"" + 3*x2
                    + "\" y2=\"" + 3*y2 + "\" style=\"stroke:rgb(255,0,0);stroke-width:3\" />";
        }
        maxX = maxX - minX; maxY = maxY - minY;
        currentSvg = "<html> <svg width='" + (3*maxX) + "' height='" + (3*maxY) + "'>" + currentSvg + "</svg> </html>";
        Files.writeString(currentFile.toPath(), currentSvg);
    }
    
    public static void hilbert(int n) throws IOException {
        begin("hilbert.html");
        // your code here...
        end();
    }
}
