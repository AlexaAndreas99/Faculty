package View;

import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Collectors;

public class FunctionalProgramming {

    public static void main(String[] args) {
        List<String> words = Arrays.asList("hi", "hello", "bef", "teh");

        // P1
        words.forEach(word -> System.out.println("  " + word));



        //p3r
        List<String> excitingWords=words.stream().map(s->s+"!").collect(Collectors.toList());
        List<String> eyeWords=words.stream().map(s->s.replace("i","eye")).collect(Collectors.toList());
        List<String> upperCaseWords=words.stream().map(String::toUpperCase).collect(Collectors.toList());

        //p4r
        List<String> shortWords = words.stream().filter(s->s.length()<4).collect(Collectors.toList());
        List<String> WordsB = words.stream().filter(s->s.contains("b")).collect(Collectors.toList());
        List<String> evenWords = words.stream().filter(s->s.length()%2==0).collect(Collectors.toList());

        //p5r

                 words.stream()
                .map(String::toUpperCase)
                .filter(s->s.length()<4)
                .filter(s->s.contains("E"))
                .limit(1)
                .forEach(System.out::println);

        //p6r
        String l=words.stream().reduce("",(acc,word)->acc+word.toUpperCase());

        //p7r
        String l7=words.stream().map(String::toUpperCase).reduce("",(acc,word)->acc+word);
        //p8r
        String l8=words.stream().reduce((acc,word)->acc+','+word).get();

        //p9r
        long n=words.stream().map(String::length).reduce(0,Integer::sum);
        //p10r
        long n10=words.stream().filter(s->s.contains("h")).count();

        List<Integer> nmb=Arrays.asList(1,2,3,4,5,6,7,8,9,10);
        String l22=nmb.stream().filter(i->i%3==0||i%2==0).map(Object::toString).reduce("",(acc, i)-> acc+"A"+Integer.toString(Integer.parseInt(i+1))+"B");

        List<Integer> l23=Arrays.asList(nmb.stream().filter(i->i%4==0).map(i->Integer.sum(i,1)).reduce(0,Integer::sum)%2);

        List<Integer> l24=Arrays.asList(nmb.stream().filter(i->i%3==0||i%7==0).map(i->Integer.sum(i,-1)).reduce(0,Integer::sum)%5);


        List<Integer> ler=Arrays.asList(nmb.stream().filter(i->i%4==0).map(i->Integer.sum(i,1)).reduce(0,Integer::sum)%2);










//        // P2
//        Consumer<String> printWord = (word) -> System.out.println(word);
//        words.forEach(printWord);
//
//        // P3
//        List<String> excitingWords = words.stream()
//                .map(w -> w + "!")
//                .collect(Collectors.toList());
//        List<String> eyeWords = words.stream()
//                .map(w -> w.replace("i", "eye"))
//                .collect(Collectors.toList());
//        List<String> upperCaseWords = words.stream()
//                .map(String::toUpperCase)
//                .collect(Collectors.toList());
//
//        // P4
//        List<String> shortWords = words.stream()
//                .filter(s -> s.length() < 4)
//                .collect(Collectors.toList());
//        List<String> wordsWithB = words.stream()
//                .filter(s -> s.contains("b"))
//                .collect(Collectors.toList());
//        List<String> evenLengthWords = words.stream()
//                .filter(s -> s.length() % 2 == 0)
//                .collect(Collectors.toList());
//
//        // P5
        words.stream()
                .map(String::toUpperCase)
                .filter(w -> w.length() < 4)
                .filter(w -> w.contains("E"))
                .limit(1)
                .forEach(System.out::println);
//
//        // P6
//        String p6 = words.stream()
//                .reduce("", (acc, word) -> acc + word.toUpperCase());
//        //System.out.println(p6);
//
//        // P7
//        String p7 = words.stream()
//                .map(String::toUpperCase)
//                .reduce("", (acc, word) -> acc + word);
//
//        // P8
//        String p8 = words.stream()
//                .reduce((acc, word) -> acc + "," + word)
//                .get();
//
//        // P9
//        int p9 = words.stream()
//                .map(String::length)
//                .reduce(0, Integer::sum);
//
//        // P10
//        long p10 = words.stream()
//                .filter(w -> w.contains("h"))
//                .count();

    }
}