def recognize_speech():
    recognizer = sr.Recognizer()
    mic = sr.Microphone()

    print("Script started from QT")
    sys.stdout.flush()

    try:
        with mic as source:
            print("Starting...")
            sys.stdout.flush()
            recognizer.adjust_for_ambient_noise(source)
            print("Parlez maintenant... (Ctrl+C pour quitter)")
            sys.stdout.flush()

            # Capture audio until one word is recognized
            audio = recognizer.listen(source)  # Capture l'audio

            print("Processing audio...")
            sys.stdout.flush()

            try:
                print("Recognizing text...")
                sys.stdout.flush()

                recognized_text = recognizer.recognize_google(audio, language="fr-FR")
                print(f"Recognized text: {recognized_text}")
                sys.stdout.flush()

                print(f"Final recognized text: {recognized_text}")
                sys.stdout.flush()
                
                # Retourner le premier mot reconnu
                return recognized_text  # Nous retournons uniquement le texte reconnu

            except sr.UnknownValueError:
                print("Impossible de comprendre l'audio.")
                sys.stdout.flush()
            except sr.RequestError:
                print("Erreur lors de la demande à l'API de reconnaissance vocale.")
                sys.stdout.flush()

    except Exception as e:
        print(f"Une erreur est survenue: {e}")
        sys.stdout.flush()
