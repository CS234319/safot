import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class HilbertCurves {

    public enum Direction { UP, RIGHT, DOWN, LEFT;}

    private static void draw(List<Direction> directions, String fileName) throws IOException {
        File currentFile = new File(fileName);
        currentFile.createNewFile();
        int currentX = 0;
        int currentY = 0;
        int maxX = Integer.MIN_VALUE;
        int maxY = Integer.MIN_VALUE;
        int minX = Integer.MAX_VALUE;
        int minY = Integer.MAX_VALUE;
        List<int[]> points = new ArrayList<>();
        for(Direction direction : directions) {
            int x1 = currentX * 30;
            int y1 = currentY * 30;
            currentX += direction == Direction.RIGHT ? 1 : direction == Direction.LEFT ? -1 : 0;
            currentY += direction == Direction.UP ? 1 : direction == Direction.DOWN ? -1 : 0;
            int x2 = currentX * 30;
            int y2 = currentY * 30;
            maxX = Math.max(x1, Math.max(maxX, x2));
            maxY = Math.max(y1, Math.max(maxY, y2));
            points.add(new int[] {x1, y1, x2, y2});
        }
        String currentSvg = "";

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
        // your code here...
    }
}
