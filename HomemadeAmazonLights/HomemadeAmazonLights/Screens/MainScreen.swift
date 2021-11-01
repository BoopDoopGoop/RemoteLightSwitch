
import SwiftUI

struct MainScreen: View {
    
    @State private var buttonPressed:Bool = false
    @State private var showActionSheet: Bool = false
    @State private var isEnabled: Bool = false
    
    var body: some View {
        ZStack {
            Image("background").resizable().ignoresSafeArea()
            Circle()
                .strokeBorder(lineWidth: Constants.circleBorderWidth)
                .frame(width: Constants.screenHeight / 4, height: Constants.screenHeight / 4, alignment: /*@START_MENU_TOKEN@*/.center/*@END_MENU_TOKEN@*/)
                .background(
                    Circle()
                        .foregroundColor(.black)
                        .opacity(self.buttonPressed ? Constants.circlePressOpacity : Constants.circleStartOpacity)
                        .frame(width: Constants.screenHeight / 4, height: Constants.screenHeight / 4, alignment: /*@START_MENU_TOKEN@*/.center/*@END_MENU_TOKEN@*/)
                        .onTapGesture {
                            print("Button Tapped")
                            let deadline = DispatchTime.now() + Constants.debounce
                            Toggle()
                            DispatchQueue.main.asyncAfter(deadline: deadline) {
                                self.isEnabled = true
                            }
                        }
                        .onLongPressGesture(minimumDuration: 5) {
                            self.showActionSheet.toggle()
                        }
                        .simultaneousGesture(
                            DragGesture(minimumDistance: 0)
                                .onChanged({_ in
                                    self.buttonPressed = true
                                })
                                .onEnded({_ in
                                    self.buttonPressed = false
                                })
                        )
                )
                .actionSheet(isPresented: $showActionSheet, content: {self.actionSheet})
        }
    }
    
    var actionSheet: ActionSheet {
        ActionSheet(title: Text("Administrative Options"), buttons: [
            .default(Text("Attach"), action: {Attach()}),
            .default(Text("Detach"), action: {Detach()}),
            .destructive(Text("Reset"), action: {Reset()})
        ])
    }
    
    func Toggle() {
        if self.isEnabled {
            guard let url = URL(string: "http://192.168.1.10") else {
                print("Server is down")
                return
            }
            var request = URLRequest(url: url)
            request.httpMethod = "GET /?TOGGLE"
            
            URLSession.shared.dataTask(with: request) { data, response, error in
            }.resume()
            
            self.isEnabled = false
        }
    }
    
    func Attach() {
        guard let url = URL(string: "http://192.168.1.10") else {
            print("Server is down")
            return
        }
        var request = URLRequest(url: url)
        request.httpMethod = "GET /?ATTACH"
        
        URLSession.shared.dataTask(with: request) { data, response, error in
        }.resume()
    }
    
    func Detach() {
        guard let url = URL(string: "http://192.168.1.10") else {
            print("Server is down")
            return
        }
        var request = URLRequest(url: url)
        request.httpMethod = "GET /?DETACH"
        
        URLSession.shared.dataTask(with: request) { data, response, error in
        }.resume()
    }
    
    func Reset() {
        guard let url = URL(string: "http://192.168.1.10") else {
            print("Server is down")
            return
        }
        var request = URLRequest(url: url)
        request.httpMethod = "GET /?RESET"
        
        URLSession.shared.dataTask(with: request) { data, response, error in
        }.resume()
    }
}
