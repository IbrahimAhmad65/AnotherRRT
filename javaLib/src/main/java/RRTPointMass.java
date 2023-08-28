import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RRTPointMass {
    private Tree tree;
    private Node goal;
    private Node start;
    private double goalRadius;
    private final int MAX_ITERATIONS = 50000;
    private static double maxAccel = 10;
    private static int tresholdToGiveUpOnsNeighbors = 50;

    public RRTPointMass(Node start, Node goal, double goalRadius) {
        this.start = start;
        this.goal = goal.setTime(Double.MAX_VALUE);
        this.goalRadius = goalRadius;
        this.tree = new Tree();
    }

    public List<Node> rrt_() {
        start = new Node(start.getX(), start.getY(), start.getVX(), start.getVY(), null, 0);
        tree = tree.AddNode(start);
        Node goalNode = new Node(goal.getX(), goal.getY(), goal.getVX(), goal.getVY(), null, Double.MAX_VALUE);
        for (int i = 0; i < MAX_ITERATIONS; i++) {
            Node rand = findRandomNode(3, 3);

            // use find optimal parent if finding collisions is cheap. If its expensive use
            // nearest + rewire
            Node nearest = findOptimalParent(rand, tree);
            Node newNode = extend(nearest, rand);
            if (newNode.getTime() < goalNode.getTime()) {
                newNode = newNode.setParent(nearest);
                tree = tree.AddNode(newNode);
            }
            // rewire(newNode, tree);
            if (findDistance(newNode, goal) < goalRadius && goalNode.getTime() > newNode.getTime()) {
                goalNode = newNode;
                System.out.println(goalNode.getTime());
            }
        }
        return getPathFromTree(tree, goalNode);
    }

    public static Node extend(Node start, Node end) {
        Node newNode = new Node(end);

        CubicHermite.Cubic xCubic = CubicHermite.computeCubic(new CubicHermite.Knot(start.getX(),
                start.getVX()),
                new CubicHermite.Knot(end.getX(), end.getVX()));
        CubicHermite.Cubic yCubic = CubicHermite.computeCubic(new CubicHermite.Knot(start.getY(),
                start.getVY()),
                new CubicHermite.Knot(end.getY(), end.getVY()));
        newNode = newNode.setTime(start.getTime() + CubicHermite.getSecondsToTraverse(xCubic, yCubic, maxAccel));
        return newNode;
    }

    public static double getTimeBetween(Node start, Node end) {
        CubicHermite.Cubic xCubic = CubicHermite.computeCubic(new CubicHermite.Knot(start.getX(),
                start.getVX()),
                new CubicHermite.Knot(end.getX(), end.getVX()));
        CubicHermite.Cubic yCubic = CubicHermite.computeCubic(new CubicHermite.Knot(start.getY(),
                start.getVY()),
                new CubicHermite.Knot(end.getY(), end.getVY()));
        return CubicHermite.getSecondsToTraverse(xCubic, yCubic, maxAccel);
    }

    public static double getTotalTime(Node parent, Node current) {
        return parent.getTime() + getTimeBetween(parent, current);
    }

    public static Tree rewire(Node nodeToBeRewired, Tree tree) {
        List<Node> neighbors = findNeighbors(nodeToBeRewired, tree, 100);
        for (Node neighbor : neighbors) {
            Node newNodeToBeRewired = extend(neighbor, nodeToBeRewired);
            if (isBetter(neighbor, newNodeToBeRewired)) {
                tree = tree.removeNode(nodeToBeRewired);
                nodeToBeRewired = extend(neighbor, nodeToBeRewired);
                nodeToBeRewired = nodeToBeRewired.setParent(neighbor);
                tree = tree.AddNode(nodeToBeRewired);
            }
        }
        return tree;
    }

    public static boolean isBetter(Node currentNode, Node modifiedVersion) {
        return modifiedVersion.getTime() < currentNode.getTime();

    }

    public static List<Node> findNeighbors(Node node, Tree tree, double radius) {
        if (radius > tresholdToGiveUpOnsNeighbors) {
            return tree.getNodes();
        }

        List<Node> neighbors = new ArrayList<Node>();
        for (Node n : tree.getNodes()) {
            if (findDistance(node, n) < radius) {
                neighbors.add(n);
            }
        }
        return neighbors;
    }

    public static final Node findRandomNode(double maxX, double maxY) {
        var r = new Random();
        double x = r.nextDouble() * maxX;
        double y = r.nextDouble() * maxY;
        double vx = 1 * (r.nextDouble() - .5);
        double vy = 1 * (r.nextDouble() - .5);
        return new Node(x, y, vx, vy, null, 0);
    }

    public static List<Node> getPathFromTree(Tree tree, Node goal) {
        List<Node> path = new ArrayList<Node>();
        Node current = goal;
        while (current.getParent() != null) {
            current = current.getParent();
            path.add(0, current);
        }
        return path;
    }

    public static boolean hasPath(Node goal) {
        return goal.getParent() != null;
    }

    public static Node findOptimalParent(Node n, Tree tree) {
        Node optimalParent = n;
        double currentOptimalParentTime = Double.MAX_VALUE;
        for (Node node : tree.getNodes()) {
            double checkTime = getTotalTime(node, n);
            if (checkTime < currentOptimalParentTime) {
                optimalParent = node;
                currentOptimalParentTime = checkTime;
            }
        }
        return optimalParent;
    }

    public static final Node findNearestNodeEuclid(Node n, Tree tree) {
        Node outNode = new Node(n);
        double minDistance = Double.MAX_VALUE;
        for (Node node : tree.getNodes()) {
            double distance = findDistance(n, node);
            if (distance < minDistance) {
                minDistance = distance;
                outNode = node;
            }
        }
        return outNode;
    }

    public static double findDistance(Node start, Node end) {
        return findDistance2D(start, end);
        // return findDistance4D(start, end);
    }

    public static double findDistance4D(Node start, Node end) {
        return Math.sqrt(Math.pow(start.getX() - end.getX(), 2) + Math.pow(start.getY() - end.getY(), 2)
                + Math.pow(start.getVX() - end.getVX(), 2) + Math.pow(start.getVY() - end.getVY(), 2));
    }

    public static double findDistance2D(Node start, Node end) {
        return Math.sqrt(Math.pow(start.getX() - end.getX(), 2) + Math.pow(start.getY() - end.getY(), 2));
    }

    public static void main(String[] args) {
        ArrayList<Node> path = new ArrayList<Node>();
        for (int i = 0; i < 1; i++) {

            RRTPointMass rrt = new RRTPointMass(
                    new Node(1, 1, 1, -1, null, 0),
                    new Node(2, 2, 0, -1, null, 0),
                    .1);
            path = (ArrayList<Node>) rrt.rrt_();
        }
        Tree printout = new Tree(path);
        System.out.println("------------------");
        System.out.println(printout);
        // Node n1 = new Node(0, 0, 1, 0, null, 0);
        // Node n2 = new Node(5, 5, 1, 1, null, 0);
        // System.out.println(RRTPointMass.extend(n1, n2, null, null, maxAccel,
        // maxAccel).getTime());
    }

}
