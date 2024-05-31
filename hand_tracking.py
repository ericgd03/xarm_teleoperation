import cv2
import mediapipe as mp

mp_holistic = mp.solutions.holistic
mp_drawing = mp.solutions.drawing_utils
mp.drawing_styles = mp.solutions.drawing_styles

coordinates = [0, 0, 0]

def teleoperation():
    cap = cv2.VideoCapture(0)

    # Initialized holistic model
    holistic = mp_holistic.Holistic(min_detection_confidence=0.5, min_tracking_confidence=0.5)

    while cap.isOpened():
        status, frame = cap.read()

        if not status:
            break

        # Transform frame
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Inference
        results = holistic.process(rgb_frame)

        # Left hand
        mp_drawing.draw_landmarks(frame, results.left_hand_landmarks, mp_holistic.HAND_CONNECTIONS)

        # Right hand
        mp_drawing.draw_landmarks(frame, results.right_hand_landmarks, mp_holistic.HAND_CONNECTIONS)

        if results.right_hand_landmarks:
            right_hand_landmark = results.right_hand_landmarks.landmark

            coordinates[0], coordinates[1] = right_hand_landmark[9].x, right_hand_landmark[9].y
            cord = str(round(coordinates[0], 3)*0.7) + "," + str(round(coordinates[1], 3)*0.7) + "," + str(round(coordinates[2], 3)*0.7)

            with open("\\\wsl.localhost\\Ubuntu-22.04\\home\\dfray1367\\prueba.txt", "w") as file:
                print(cord)
                file.write(cord)

        if results.left_hand_landmarks:
            left_hand_landmark = results.left_hand_landmarks.landmark

            coordinates[2] = left_hand_landmark[9].y
            cord = str(round(coordinates[0], 3) * 0.8) + "," + str(round(coordinates[1], 3) * 0.8) + "," + str(round(coordinates[2], 3) * 0.8)

            with open("\\\wsl.localhost\\Ubuntu-22.04\\home\\dfray1367\\prueba.txt", "w") as file:
                print(cord)
                file.write(cord)

        # Display
        cv2.imshow("frame", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()

if __name__ == '__main__':
    teleoperation()