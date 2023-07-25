from color import *

def main():
    photo = True
    cap = cv2.VideoCapture(1)
    while True:
        ret, frame = cap.read()
 
        if not ret:
            break

        frame = cv2.flip(frame, 1)
        if photo:
            cv2.imwrite("5cubes_2.png", frame)
            photo = False
        final_frame = detect_color(frame)

        cv2.imshow('Video', final_frame)

        # Exit when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

main()