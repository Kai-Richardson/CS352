// Converts grade strings to GPAs
fn gpa_for(grade: &str) -> Option<f64> {
    match grade {
        "A" => Some(4.0),
        "B" => Some(3.0),
        "C" => Some(2.0),
        "D" => Some(1.0),
        "F" => Some(0.0),
        _ => None,
    }
}

fn gpa(letters: Vec<&str>) -> f64 {
    let mut sum = 0.0;
    let mut n = 0;

    for letter in letters {
        if let Some(grade) = gpa_for(letter) {
            sum += grade;
            n += 1;
        }
    }

    if n > 0 { sum / f64::from(n) } else { 0.0 }
}

fn main() {
    let grade = "A";
    if let Some(gpa) = gpa_for(grade) {
        println!("{} = {:.1}", grade, gpa);
    } else {
        println!("Invalid grade {}", grade);
    }

    let mut grades = vec!["A", "C", "A"];
    grades.push("B");
    println!("Term GPA is {}", gpa(grades));

    let n = 5;
    for i in 0..n {
        println!("{}", i)
    }
}

