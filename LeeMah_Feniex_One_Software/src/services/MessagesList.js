import  React, { Component } from  'react';



import  MessageService  from  './MessageService';

// import  RecruiterFlowService  from  './RecruiterFlowService';
const  MessageServices  =  new  MessageService();


class  MessagesList  extends  Component {

    constructor(props) {
        super(props);
        this.state  = {
            Candidates: [],
            nextPageURL:  ''
        };
        this.nextPage  =  this.nextPage.bind(this);
        this.handleDelete  =  this.handleDelete.bind(this);
    }

    componentDidMount() {
        var  self  =  this;
        MessageServices.getMessages().then(function (result) {
            console.log("This is the LSD: "+result.data)
            self.setState({ Candidates:  result.data, nextPageURL:  result.nextlink})
        });
    }

    handleDelete(e,pk){
        var  self  =  this;
        MessageServices.deleteMessage({pk :  pk}).then(()=>{
            var  newArr  =  self.state.Candidates.filter(function(obj) {
                return  obj.pk  !==  pk;
            });
            self.setState({Candidates:  newArr})
        });
    }

    nextPage(){
        var  self  =  this;
        MessageServices.getMessagesByURL(this.state.nextPageURL).then((result) => {
            self.setState({ Candidates:  result.data, nextPageURL:  result.nextlink})
        });
    }

    render() {

        return (
        <div  className="Candidates--list">
            <table  className="table">
                <thead  key="thead">
                <tr>
                    <th>#</th>
                    <th>First Name</th>
                    <th>Last Name</th>
                    <th>Phone</th>
                    <th>Email</th>
                    <th>Address</th>
                    <th>Description</th>
                    <th>Actions</th>
                </tr>
                </thead>
                <tbody>
                    {this.state.Candidates.map( c  =>
                    <tr  key={c.pk}>
                        <td>{c.pk}  </td>
                        <td>{c.first_name}</td>
                        <td>{c.last_name}</td>
                        <td>{c.phone}</td>
                        <td>{c.email}</td>
                        <td>{c.address}</td>
                        <td>{c.description}</td>
                        <td>
                        <button  onClick={(e)=>  this.handleDelete(e,c.pk) }> Delete</button>
                        <a  href={"/Candidate/" + c.pk}> Update</a>
                        </td>
                    </tr>)}
                </tbody>
            </table>
            <button  className="btn btn-primary"  onClick=  {  this.nextPage  }>Next</button>
        </div>
        );
    }
}
export  default  CandidatesList;

