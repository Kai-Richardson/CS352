import HW2

main =
    let
        inp = "CS 203 B 3 Jean-Luc Picard C\nPHL 220 A 3 Ada Lovelace A\nPHL 220 A 3 Grace Hopper C\nTHE 105 A 3 Grace Hopper B+"
        ls = ["CS 203 B 3 Jean-Luc Picard C","PHL 220 A 3 Ada Lovelace A","PHL 220 A 3 Grace Hopper C","THE 105 A 3 Grace Hopper B+"]
        rs = [("CS",203,"B",3,"Picard, Jean-Luc",2.0),("PHL",220,"A",3,"Lovelace, Ada",4.0),("PHL",220,"A",3,"Hopper, Grace",2.0),("THE",105,"A",3,"Hopper, Grace",3.3)]
        srs = [[("PHL",220,"A",3,"Hopper, Grace",2.0),("THE",105,"A",3,"Hopper, Grace",3.3)],[("PHL",220,"A",3,"Lovelace, Ada",4.0)],[("CS",203,"B",3,"Picard, Jean-Luc",2.0)]]
        ss = [("Hopper, Grace",2.65,6),("Lovelace, Ada",4.0,3),("Picard, Jean-Luc",2.0,3)]
    in do
        putStrLn "\n== splitLines =="
        print (splitLines inp)
        putStrLn "\n== parseRecord =="
        print [parseRecord l | l <- ls ]
        putStrLn "\n== sortAndGroupRecords =="
        print (sortAndGroupRecords rs)
        putStrLn "\n== calcGpa =="
        print [calcGpa sr | sr <- srs]
        putStrLn "\n== formatRecord =="
        print [formatRecord s | s <- ss]
        putStrLn "\n== computeGpas =="
        putStr (computeGpas inp)
