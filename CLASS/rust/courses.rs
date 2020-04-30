pub struct Course {
    pub subject: String,
    pub course_num: u16,
    pub student: String,
    pub grade: f64
}

impl Course {
    fn new(subject: &str, course_num: u16, student: &str, grade: f64) -> Self {
        Course{
            subject: String::from(subject), course_num,
            student: String::from(student), grade
        }
    }
}

fn main() {
    let mut courses = vec![];
    courses.push(Course {
        subject: String::from("CS"),
        course_num: 352,
        student: String::from("Foo Bar"),
        grade: 3.3
    });
    courses.push(Course::new("CS", 203, "Baz Bar", 2.7));

    for course in courses {
        println!("{} {}", course.subject.as_str(), course.course_num);
    }
}

//fn long_subject(sub: &str) -> &str