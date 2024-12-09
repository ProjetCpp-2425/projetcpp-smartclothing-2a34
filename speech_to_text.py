import speech_recognition as sr
import sys

def recognize_speech():
    recognizer = sr.Recognizer()
    mic = sr.Microphone()

    print("Script started from Qt")
    sys.stdout.flush()

    try:
        with mic as source:
            print("Starting...")
            sys.stdout.flush()
            recognizer.adjust_for_ambient_noise(source)
            print("Parlez maintenant... (Ctrl+C pour quitter)")
            sys.stdout.flush()

            # Capture audio
            audio = recognizer.listen(source)

            print("Processing audio...")
            sys.stdout.flush()

            try:
                print("Recognizing text...")
                sys.stdout.flush()

                recognized_text = recognizer.recognize_google(audio, language="fr-FR")
                print(f"Recognized text: {recognized_text}")
                sys.stdout.flush()

                return recognized_text

            except sr.UnknownValueError:
                print("Impossible de comprendre l'audio.")
                sys.stdout.flush()
            except sr.RequestError:
                print("Erreur lors de la demande à l'API de reconnaissance vocale.")
                sys.stdout.flush()

    except Exception as e:
        print(f"Une erreur est survenue: {e}")
        sys.stdout.flush()

if __name__ == "__main__":
    recognize_speech()
