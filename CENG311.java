package ceng311;
import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

public class CENG311 {
    public static void main(String args[]) throws IOException {
        File file = new File("20integer.txt");
        ArrayList<Integer> integerArrayList = new ArrayList<Integer>();
        Scanner scan = new Scanner(file);
        while(scan.hasNext()){
            integerArrayList.add(scan.nextInt());
        }
        scan.close();
        PriorityQueue<Integer> p_queue = new PriorityQueue<>(Comparator.reverseOrder());
        long start = System.currentTimeMillis();
        for (int number:integerArrayList
        ) {
            p_queue.add(number);
        }
        long end = System.currentTimeMillis();
        float sec = (end - start) / 1000F;
        System.out.println("Spent time is "+sec + " seconds");
        BufferedWriter writer = new BufferedWriter(new FileWriter("result_20integer.txt"));
        while (!p_queue.isEmpty()) {
            writer.append(p_queue.poll().toString()+" ");
        }
        writer.close();
    }
}